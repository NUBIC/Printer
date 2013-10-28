#include "stdafx.h"
#include "SpoolStatus.h"
#include "SpoolStatusEnum.h"


SpoolStatus::SpoolStatus(SpoolStatusEnum::Enum status, DWORD printJobIdentifier) {
	this->status = status;
	this->printJobIdentifier = printJobIdentifier;
}


DWORD SpoolStatus::getPrintJobIdentifier() {
	return this->printJobIdentifier;
}

bool SpoolStatus::isSuccessfull() {
	return !(this->status == SpoolStatusEnum::Enum::FAILURE);
}

LPTSTR SpoolStatus::getStatus() {
	return SpoolStatusEnum::toString(this->status);
}