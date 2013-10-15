#pragma once

#include <tchar.h>

class SpoolStatus;

class Cli
{
private:
	int argc;
	_TCHAR** argv;
	void help();
	bool isHelpSwitch(_TCHAR* arg);
	bool fileExists(_TCHAR* filename);
	SpoolStatus* spool(_TCHAR* arg1, _TCHAR* arg2);
public:
	Cli(int argc, _TCHAR* argv[]);
	void run();
};

