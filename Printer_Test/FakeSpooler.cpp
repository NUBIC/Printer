#include "stdafx.h"
#include "FakeSpooler.h"
#include "SpoolStatus.h"


SpoolStatus* FakeSpooler::spool(LPTSTR printerName, LPTSTR filePath) {
	SpoolStatus* s = new SpoolStatus(SpoolStatusEnum::Enum::SPOOLING, 123);
	return s;
}

SpoolStatus* FakeSpooler::queryPrintJob(LPSTR printerName, DWORD jobId) {
	return NULL;
}
