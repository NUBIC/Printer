#pragma once

#include <tchar.h>

class Spooler;
class SpoolStatus;

class Cli
{
private:
	int argc;
	_TCHAR** argv;
	Spooler* spooler;
	void help();
	bool isHelpSwitch(_TCHAR* arg);
	bool fileExists(_TCHAR* filename);
public:
	Cli(int argc, _TCHAR* argv[]);
	void run();
	void setSpooler(Spooler* spooler);
};

