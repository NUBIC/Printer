#pragma once

#include <Windows.h>
#include "SpoolStatusEnum.h"

class SpoolStatus
{
private:
	SpoolStatusEnum::Enum status;
	DWORD printJobIdentifier;
public:
	SpoolStatus(SpoolStatusEnum::Enum status, DWORD printJobIdentifier);

	DWORD getPrintJobIdentifier();
	LPTSTR getStatus();
	bool isSuccessfull();
};

