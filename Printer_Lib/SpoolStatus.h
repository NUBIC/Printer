#pragma once
class SpoolStatus
{
private:
	DWORD printJobIdentifier;
public:
	SpoolStatus(DWORD printJobIdentifier);

	DWORD getPrintJobIdentifier();
};

