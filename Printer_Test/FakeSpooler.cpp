#include "stdafx.h"
#include "FakeSpooler.h"
#include "SpoolStatus.h"


SpoolStatus* FakeSpooler::spool(LPTSTR printerName, LPTSTR filePath) {
	SpoolStatus* s = new SpoolStatus(123);
	return s;
}