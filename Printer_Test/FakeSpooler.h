#pragma once

#include <SpoolerInterface.h>

class FakeSpooler : public SpoolerInterface
{
public:
	SpoolStatus* spool(LPTSTR printerName, LPTSTR filePath);
	SpoolStatus* queryPrintJob(LPSTR printerName, DWORD jobId);
};

