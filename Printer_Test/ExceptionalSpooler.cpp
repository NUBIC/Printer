#include "stdafx.h"
#include "ExceptionalSpooler.h"
#include "SpoolException.h"

SpoolStatus* ExceptionalSpooler::spool(LPTSTR printerName, LPTSTR filePath) {
	throw SpoolException("I am exceptional!");
}
