#include "stdafx.h"
#include "CppUnitTest.h"
#include "Cli.h"
#include <tchar.h>
#include <iostream>
#include <string>
#include <wchar.h>
#include "SpoolStatus.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

//SpoolStatus* Cli::spool(LPTSTR printerName, LPTSTR filePath) {
//	return new SpoolStatus(123);
//}

namespace Printer_Test
{
	TEST_CLASS(CliTest)
	{
	public:
		TEST_CLASS_INITIALIZE(ClassInitialize)
		{
			Logger::WriteMessage("In Class Initialize");
		}

		TEST_METHOD(TestFileNotFound)
		{
			std::wstringstream buffer;
			std::wstreambuf* old = std::wcout.rdbuf(buffer.rdbuf());
			_TCHAR *argv[] = {
				L"Printer",
				L"hp-printer",
				L"invalid.txt"
			};
			Cli *c = new Cli(3, argv);
			c->run();
			
			buffer.seekg(0, buffer.end);
			int length = buffer.tellg();
			buffer.seekg(0, buffer.beg);
			_TCHAR * b = new _TCHAR[length];
			buffer.read(b, length);

			const _TCHAR * expected = L"Failed to open the file 'invalid.txt'";
			const _TCHAR * found = wcsstr(b, expected);
			wchar_t msgBuffer[1000];
			swprintf(msgBuffer, L"Expected: %ls, Actual: %ls", expected, b);
			Assert::IsNotNull(found, msgBuffer);
		}

		TEST_METHOD(TestSuccessfulSpool)
		{
			std::wstringstream buffer;
			std::wstreambuf* old = std::wcout.rdbuf(buffer.rdbuf());
			_TCHAR *argv[] = {
				L"Printer",
				L"hp-printer",
				L"../Printer_Test/valid.txt"
			};
			Cli *c = new Cli(3, argv);
			c->run();
			
			buffer.seekg(0, buffer.end);
			int length = buffer.tellg();
			buffer.seekg(0, buffer.beg);
			_TCHAR * b = new _TCHAR[length];
			buffer.read(b, length);

			const _TCHAR * expected = L"Successfully spooled '../Printer_Test/valid.txt' to printer 'hp-printer'\nJob identifier is '123'";
			const _TCHAR * found = wcsstr(b, expected);
			wchar_t msgBuffer[1000];
			swprintf(msgBuffer, L"Expected: %ls, Actual: %ls", expected, b);
			Assert::IsNotNull(found, msgBuffer);
		}

	};
}