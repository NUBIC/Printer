#pragma once

#include <SpoolerInterface.h>

class FakeSpooler : public SpoolerInterface
{
public:
	//FakeSpooler(void);
	SpoolStatus* spool(LPTSTR printerName, LPTSTR filePath);
};

