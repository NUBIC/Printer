#include "stdafx.h"
#include <iostream>
#include "Cli.h"

int _tmain(int argc, _TCHAR* argv[]) {
	Cli* cli = new Cli(argc, argv);
	cli->run();
	return 0;
}
