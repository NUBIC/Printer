#pragma once

#include "SpoolerInterface.h"

class ExceptionalSpooler : public SpoolerInterface

{
public:
	SpoolStatus* spool(LPTSTR printerName, LPTSTR filePath);
	SpoolStatus* queryPrintJob(LPSTR printerName, DWORD jobId);
};

