#include "stdafx.h"
#include "Cli.h"
#include <iostream>
#include <wchar.h>
#include <fstream>

using namespace std;

Cli::Cli(int argc, _TCHAR* argv[]) {
	this->argc = argc;
	//_TCHAR** argvv;
	//argvv = argv;
	this->argv = argv;
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
		_TCHAR* arg2 = argv[2];
		if (fileExists(arg2)) {
			// Print
		} else {
			cout << endl;
			wcout << "Failed to open the file '" << arg2 << "'" << endl;
		}
	}
}

bool Cli::isHelpSwitch(_TCHAR* arg) {
	return wcscmp(arg,L"/h") == 0;
}

void Cli::help() {
	cout << endl;
	cout << "Sends a file to a printer and queries it's status" << endl;
	cout << endl;
	cout << "PRINTER [/h] <printer> <file>" << endl;
	cout << "\t" << "/h" << "\t\t" << "Displays this help message" << endl;
	cout << "\t" << "<printer>" << "\t" << "The printer which will print the file" << endl;
	cout << "\t" << "<file>" << "\t\t" << "The file to be printed" << endl;
}

bool Cli::fileExists(_TCHAR* filename) {
	ifstream ifile(filename);
	return ifile != NULL;
}