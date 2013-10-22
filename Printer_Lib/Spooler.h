#pragma once

#include <Windows.h>
#include "SpoolerInterface.h"

class SpoolStatus;

class Spooler : public SpoolerInterface {

public:
	SpoolStatus* spool(LPTSTR printerName, LPTSTR filePath);

};