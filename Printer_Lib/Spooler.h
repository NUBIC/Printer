#ifndef SPOOLER_H
#define SPOOLER_H

#include <Windows.h>

class SpoolStatus;

class Spooler {

public:
	static SpoolStatus* spool(LPTSTR printerName, LPTSTR filePath);

};

#endif /* SPOOLER_H */