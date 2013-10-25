#include "stdafx.h"
#include "Cli.h"
#include <iostream>
#include <wchar.h>
#include <fstream>
#include "Spooler.h"
#include "SpoolStatus.h"
#include "SpoolException.h"
#include "Version.h"

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
 *   => { "status":"success", print_job_identifier:123 }
 *   =>
 *   => Printer.exe /json "HP InkJet" badfile.doc
 *   => { "status":"failure", "message":"File does not exist"}
 *
 * /version
 *   The version switch displays the version of the application
 *
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
	}
	
	if (argc > 2) {
		_TCHAR* printer = argv[argc - 2];
		_TCHAR* file    = argv[argc - 1];
		if (fileExists(file)) {
			try {
				SpoolStatus* s = spooler->spool(printer, file);
				if (containsJsonSwitch(argc, argv)) {
					char* status = s->getStatus();
					wcout << "{\"status\":\"" << status << "\", \"print_job_identifier\":"<< s-> getPrintJobIdentifier() << "}";
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

void Cli::help() {
	wcout << endl;
	wcout << "Sends a file to a printer and queries it's status" << endl;
	wcout << endl;
	wcout << "PRINTER [/help] [/json] [/version] <printer> <file>" << endl;
	wcout << "\t" << "/help" << "\t\t" << "Displays this help message" << endl;
	wcout << "\t" << "/json" << "\t\t" << "Displays results in JSON" << endl;
	wcout << "\t" << "/version" << "\t" << "Displays version information" << endl;
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