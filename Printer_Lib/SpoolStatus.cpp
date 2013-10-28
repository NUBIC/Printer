#include "stdafx.h"
#include "SpoolStatus.h"


SpoolStatus::SpoolStatus(DWORD printJobIdentifier) {
	this->printJobIdentifier = printJobIdentifier;
}


DWORD SpoolStatus::getPrintJobIdentifier() {
	return this->printJobIdentifier;
}

bool SpoolStatus::isSuccessfull() {
	return this->printJobIdentifier != NULL;
}

char* SpoolStatus::getStatus() {
	return this->isSuccessfull() ? "spooling" : "failure";
}