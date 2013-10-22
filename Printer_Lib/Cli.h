#pragma once

#include <tchar.h>

class Spooler;
class SpoolStatus;
class SpoolerInterface;

class Cli
{
private:
	int argc;
	_TCHAR** argv;
	SpoolerInterface* spooler;
	void help();
	bool isHelpSwitch(_TCHAR* arg);
	bool fileExists(_TCHAR* filename);
public:
	Cli(int argc, _TCHAR* argv[]);
	void run();
	void setSpooler(SpoolerInterface* spooler);
};

