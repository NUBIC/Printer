#ifndef SPOOLER_H
#define SPOOLER_H

#include <Windows.h>

class Spooler {

public:
	static bool spool(LPTSTR printerName, LPTSTR filePath);

};

#endif /* SPOOLER_H */