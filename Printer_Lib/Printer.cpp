// Printer.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <windows.h>
#include <wingdi.h>
#include <winspool.h>
#include <exception>
#include <iostream>
#include "Printer.h"

using namespace std;

//class myexception: public std::runtime_error {
//public:
//	explicit myexception(const string& _Message) : std::runtime_error(_Message) {}
//};


int _tmain(int argc, _TCHAR* argv[])
{	
	OutputDebugString(L"Program Started...\n");

	DWORD sd = 0;
	DOC_INFO_1 docinfo = {0};
	docinfo.pDocName = L"Test";
	docinfo.pDatatype = L"raw"; // or Text
	docinfo.pOutputFile = NULL;

	HANDLE printerHandle = NULL;
	if (!OpenPrinter(L"NPI6C6DB9 (HP LaserJet 500 colorMFP M570dn)", &printerHandle, NULL)) {
		throw std::runtime_error("failed OpenPrinter");
	}
	
	sd = StartDocPrinter(printerHandle, 1, (PBYTE)&docinfo);
	if (!sd) {
		ClosePrinter(printerHandle);
		throw std::runtime_error("failed StartDocPrinter");
	}

	if (!StartPagePrinter(printerHandle)) {
		EndDocPrinter(printerHandle);
		ClosePrinter(printerHandle);
		throw std::runtime_error("failed StartPagePrinter");
	}
	
	HANDLE hFile = CreateFile(L"c:\\inetpub\\wwwroot\\hello.txt", GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	if (hFile == INVALID_HANDLE_VALUE) {
		CloseHandle(hFile);
		EndPagePrinter(printerHandle);
		EndDocPrinter(printerHandle);
		ClosePrinter(printerHandle);
		throw std::runtime_error("failed CreateFile");
	}

	char buffer[1024] = {0};

	for (int size = GetFileSize(hFile, NULL); size; )
	{
		DWORD dwRead = 0, dwWritten = 0;
		
		if (!ReadFile(hFile, buffer, min(size, sizeof(buffer)), &dwRead, NULL)) {
			break;
		}
				
		if (!WritePrinter(printerHandle, buffer, (DWORD) sizeof(buffer), &dwWritten)) {
			EndPagePrinter(printerHandle);
			EndDocPrinter(printerHandle);
			ClosePrinter(printerHandle);
			throw std::runtime_error("failed WritePrinter");
		}

		size -= dwRead;
	}

	CloseHandle(hFile);
	EndPagePrinter(printerHandle);
	EndDocPrinter(printerHandle);
	ClosePrinter(printerHandle);

	printerHandle = NULL;
	if (!OpenPrinter(L"NPI6C6DB9 (HP LaserJet 500 colorMFP M570dn)", &printerHandle, NULL)) {
		throw std::runtime_error("failed OpenPrinter");
	}

	JOB_INFO_1 *jobInfo = new JOB_INFO_1();

	
	DWORD pcbNeeded = NULL;
	DWORD pcbNeeded2 = NULL;

	for (int i = 0; i < 10; i++)
	{
		pcbNeeded = NULL;
		pcbNeeded2 = NULL;
		if (!GetJob(printerHandle,sd, 1, (LPBYTE)jobInfo, 0, &pcbNeeded)) {
			if (!GetJob(printerHandle,sd, 1, (LPBYTE)jobInfo, pcbNeeded, &pcbNeeded2)) {
				cout << "Failed GetJob: " << GetLastError() << endl;
				//throw std::runtime_error("failed GetJob");
			} else {
				if ((jobInfo->Status & JOB_STATUS_COMPLETE) == JOB_STATUS_COMPLETE) {
					cout << "Success" << endl;
				} else {
					cout << "Failed" << endl;
				}
			}
		} else {
			if (jobInfo->Status & JOB_STATUS_COMPLETE) {
				cout << "Success" << endl;
			} else {
				cout << "Failed" << endl;
			}
		}
		cin.get();
	}
	

	return 0;
}

