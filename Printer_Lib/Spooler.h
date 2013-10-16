#pragma once

#include <Windows.h>

class SpoolStatus;

class Spooler {

public:
	SpoolStatus* spool(LPTSTR printerName, LPTSTR filePath);

};