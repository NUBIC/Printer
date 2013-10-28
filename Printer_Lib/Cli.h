#pragma once

#include <tchar.h>
#include <Windows.h>

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
	bool containsJsonSwitch(int argc, _TCHAR* argv[]);
public:
	bool isJobSwitch(_TCHAR* arg);
	DWORD extractJobIdFromJobSwitch(_TCHAR* arg);
	Cli(int argc, _TCHAR* argv[]);
	void run();
	void setSpooler(SpoolerInterface* spooler);
};

