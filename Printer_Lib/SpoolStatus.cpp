#include "stdafx.h"
#include "SpoolStatus.h"


SpoolStatus::SpoolStatus(DWORD printJobIdentifier) {
	this->printJobIdentifier = printJobIdentifier;
}


DWORD SpoolStatus::getPrintJobIdentifier() {
	return this->printJobIdentifier;
}