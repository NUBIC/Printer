#include "stdafx.h"
#include "Cli.h"
#include <iostream>
#include <wchar.h>
#include <fstream>
#include "Spooler.h"
#include "SpoolStatus.h"
#include "SpoolException.h"

using namespace std;

Cli::Cli(int argc, _TCHAR* argv[]) {
	this->argc = argc;
	this->argv = argv;
	this->spooler = new Spooler();

}

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
	}
	
	if (argc > 2) {
		_TCHAR* arg1 = argv[1];
		_TCHAR* arg2 = argv[2];
		if (fileExists(arg2)) {
			try {
				SpoolStatus* s = spooler->spool(arg1, arg2);
				wcout << "Successfully spooled '"<< arg2 << "' to printer '" << arg1 << "'"<< endl;
				wcout << "Job identifier is '" << s->getPrintJobIdentifier() << "'" << endl;
			} catch (SpoolException & e) {
				wcout << e.what() << endl;
				//TODO: Print stack from exception (StackWalker)
			}
		} else {
			wcout << "Failed to open the file '" << arg2 << "'" << endl;
		}
	}
}

bool Cli::isHelpSwitch(_TCHAR* arg) {
	return wcscmp(arg,L"/h") == 0;
}

void Cli::help() {
	wcout << endl;
	wcout << "Sends a file to a printer and queries it's status" << endl;
	wcout << endl;
	wcout << "PRINTER [/h] <printer> <file>" << endl;
	wcout << "\t" << "/h" << "\t\t" << "Displays this help message" << endl;
	wcout << "\t" << "<printer>" << "\t" << "The printer which will print the file" << endl;
	wcout << "\t" << "<file>" << "\t\t" << "The file to be printed" << endl;
}

bool Cli::fileExists(_TCHAR* filename) {
	ifstream ifile(filename);
	return ifile != NULL;
}

void Cli::setSpooler(Spooler* spooler) {
	this->spooler = spooler;
}