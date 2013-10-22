#pragma once

#include <Windows.h>

class SpoolStatus
{
private:
	DWORD printJobIdentifier;
public:
	SpoolStatus(DWORD printJobIdentifier);

	DWORD getPrintJobIdentifier();
	char* getStatus();
	bool isSuccessfull();
};

