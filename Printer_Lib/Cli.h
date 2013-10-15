#pragma once
class Cli
{
private:
	int argc;
	_TCHAR** argv;
	void help();
	bool isHelpSwitch(_TCHAR* arg);
	bool fileExists(_TCHAR* filename);
public:
	Cli(int argc, _TCHAR* argv[]);
	void run();
};

