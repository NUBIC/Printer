#pragma once

#include <Windows.h>

class SpoolStatus;

class SpoolerInterface
{
public:
	virtual SpoolStatus* spool(LPTSTR printerName, LPTSTR filePath) = 0;
};

