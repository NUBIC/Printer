#include "stdafx.h"
#include "Cli.h"
#include <iostream>
#include <wchar.h>
#include <fstream>
#include "Spooler.h"
#include "SpoolStatus.h"
#include "SpoolException.h"
#include "Version.h"
#include <sstream>
#include <algorithm>

using namespace std;

Cli::Cli(int argc, _TCHAR* argv[]) {
	this->argc = argc;
	this->argv = argv;
	this->spooler = new Spooler();

}

/**
 * Interprets the arguments passed on the command-line.
 *
 * Example 1 (Printing)
 *
 *   => Printer.exe "HP Inkjet" "doc.txt"
 *
 *   argv[0] = "Printer.exe" (Executable)
 *   argv[1] = "HP Inkjet"   (Printer Name)
 *   argv[2] = "doc.txt"     (Document Name)
 *
 * Example 2 (Printing and returning a JSON status)
 *
 *   => Printer.exe /json "HP Inkjet" "doc.txt"
 *
 *   argv[0] = "Printer.exe" (Executable)
 *   argv[1] = "\json"       (Switch)
 *   argv[1] = "HP Inkjet"   (Printer Name)
 *   argv[2] = "doc.txt"     (Document Name)
 *
 * Also, switches can be used to change the behavior Printer.exe
 *
 * /help
 *   The help switch prints a help message of how to use the application
 *
 * /json
 *   The JSON Switch returns results in JSON
 * 
 *   => Printer.exe /json "HP InkJet" my.doc
 *   => { "status":"spooling", "job_id":123, "message":"The print job is spooling to the printer" }
 *   =>
 *   => Printer.exe /json "HP InkJet" badfile.doc
 *   => { "status":"failure", "message":"File does not exist"}
 *
 * /job:xxx
 *   The job switch displays the status of the specified print job.
 *
 *   => Printer.exe /job:321
 *   => { "status":"complete", "job_id":123, "message":"The print job is complete"}
 *
 *   => Printer.exe /job:999
 *   => { "status":"offline", "job_id":999, "message":"The printer is offline"}
 *
 * /version
 *   The version switch displays the version of the application
 *
 */
void Cli::run() {
	if (argc == 1) {
		help();
		return;
	}

	if (argc > 1) {
		_TCHAR* arg1 = argv[1];
		if (isHelpSwitch(arg1)) {
			help();
			return;
		}
		if (isVersionSwitch(arg1)) {
			version();
			return;
		}
		if (isJobSwitch(arg1)) {
			_TCHAR* arg2 = argv[2];
			DWORD jobId = extractJobIdFromJobSwitch(arg1);
			spooler->queryPrintJob((LPSTR) arg2, jobId);
		}
	}
	
	if (argc > 2) {
		_TCHAR* printer = argv[argc - 2];
		_TCHAR* file    = argv[argc - 1];
		if (fileExists(file)) {
			try {
				SpoolStatus* s = spooler->spool(printer, file);
				if (containsJsonSwitch(argc, argv)) {
					char* status = s->getStatus();
					wcout << "{\"status\":\"" << status << "\", \"job_id\":"<< s-> getPrintJobIdentifier() << "}";
				} else {
					wcout << "Successfully spooled '"<< file << "' to printer '" << printer << "'"<< endl;
					wcout << "Job identifier is '" << s->getPrintJobIdentifier() << "'" << endl;
				}
			} catch (SpoolException & e) {
				if (containsJsonSwitch(argc, argv)) {
					wcout << "{\"status\":\"failure\", \"message\":\"" << e.what() << "\"}";
				} else {
					wcout << e.what() << endl;
					//TODO: Print stack from exception (StackWalker)
				}
			}
		} else {
			if (containsJsonSwitch(argc, argv)) {
				wcout << "{\"status\":\"failure\", \"message\":\"Failed to open the file '" << file << "'" << "\"}";
			} else {
				wcout << "Failed to open the file '" << file << "'" << endl;
			}
		}
	}
}

bool Cli::isHelpSwitch(_TCHAR* arg) {
	return _wcsicmp(arg,L"/h") == 0 || _wcsicmp(arg,L"/help") == 0;
}

bool Cli::isVersionSwitch(_TCHAR* arg) {
	return _wcsicmp(arg,L"/version") == 0;
}

bool Cli::isJobSwitch(_TCHAR* arg) {
	return _wcsnicmp(arg,L"/job", 4) == 0;
}

DWORD Cli::extractJobIdFromJobSwitch(_TCHAR* arg) {
	wchar_t* context = NULL;
	_TCHAR seps[] = L":";
	_TCHAR* jobStr = wcstok_s(_wcsdup(arg), seps, &context);
	DWORD tmp = NULL;
	std::wstringstream(context) >> tmp;
	return tmp;
}

void Cli::help() {
	wcout << endl;
	wcout << "Sends a file to a printer and queries it's status" << endl;
	wcout << endl;
	wcout << "PRINTER [/help] [/json] [/version] <printer> <file>" << endl;
	wcout << "\t" << "/help" << "\t\t" << "Displays this help message" << endl;
	wcout << "\t" << "/json" << "\t\t" << "Displays results in JSON" << endl;
	wcout << "\t" << "/version" << "\t" << "Displays version information" << endl;
	wcout << "\t" << "/job:xxx" << "\t" << "Displays status of print job" << endl;
	wcout << "\t" << "<printer>" << "\t" << "The printer which will print the file" << endl;
	wcout << "\t" << "<file>" << "\t\t" << "The file to be printed" << endl;
}

void Cli::version() {
	wcout << "Printer " << VERSION << endl;
}

bool Cli::fileExists(_TCHAR* filename) {
	ifstream ifile(filename);
	return ifile != NULL;
}

void Cli::setSpooler(SpoolerInterface* spooler) {
	this->spooler = spooler;
}

bool Cli::containsJsonSwitch(int argc, _TCHAR* argv[]) {
	bool result = false;
	for(int i = 0; i < argc; i++) {
		if (_wcsicmp(argv[i],L"/json") == 0) {
			result = true;
		}
	}
	return result;
}