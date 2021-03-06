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
	void version();
	bool isHelpSwitch(_TCHAR* arg);
	bool isVersionSwitch(_TCHAR* arg);
	bool fileExists(_TCHAR* filename);
public:
	Cli(int argc, _TCHAR* argv[]);
	void run();
	void setSpooler(SpoolerInterface* spooler);
	bool Cli::containsJsonSwitch(int argc, _TCHAR* argv[]);
};

