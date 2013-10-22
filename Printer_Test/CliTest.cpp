#include "stdafx.h"
#include "CppUnitTest.h"
#include "Cli.h"
#include <tchar.h>
#include <iostream>
#include <string>
#include <wchar.h>
#include "SpoolStatus.h"
#include "FakeSpooler.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

//SpoolStatus* Cli::spool(LPTSTR printerName, LPTSTR filePath) {
//	return new SpoolStatus(123);
//}

namespace Printer_Test
{
	static std::wstringstream buffer;
	static std::wstreambuf* old;
	
	TEST_CLASS(CliTest)
	{
	public:
		
		TEST_CLASS_INITIALIZE(ClassInitialize)
		{
			buffer.clear();
			old = std::wcout.rdbuf(buffer.rdbuf());
		}

		static void expectOutput(_TCHAR* expected) {
			buffer.seekg(0, buffer.end);
			int length = buffer.tellg();
			buffer.seekg(0, buffer.beg);
			_TCHAR * b = new _TCHAR[length];
			buffer.read(b, length);

			const _TCHAR * found = wcsstr(b, expected);
			wchar_t msgBuffer[1000];
			swprintf(msgBuffer, L"Expected: %ls, Actual: %ls", expected, b);
			Assert::IsNotNull(found, msgBuffer);
		}

		static void runCli(_TCHAR* argv[]) {
			Cli *c = new Cli(sizeof(argv), argv);
			c->run();
		}

		static void runCli(_TCHAR* argv[], SpoolerInterface* s) {
			Cli *c = new Cli(sizeof(argv), argv);
			c->setSpooler(s);
			c->run();
		}

		TEST_METHOD(TestFileNotFound)
		{
			_TCHAR *argv[] = {
				L"Printer",
				L"hp-printer",
				L"invalid.txt"
			};
			runCli(argv);
			expectOutput(L"Failed to open the file 'invalid.txt'");
		}

		TEST_METHOD(TestSpoolSuccess)
		{
			_TCHAR *argv[] = {
				L"Printer",
				L"hp-printer",
				L"../Printer_Test/valid.txt"
			};
			runCli(argv, new FakeSpooler());
			expectOutput(L"Successfully spooled '../Printer_Test/valid.txt' to printer 'hp-printer'\nJob identifier is '123'");
		}

		TEST_METHOD(TestSpoolSuccessWithJsonSwitch) {
			_TCHAR *argv[] = {
				L"Printer",
				L"/json"
				L"hp-printer",
				L"../Printer_Test/valid.txt"
			};
			runCli(argv);
			expectOutput( L"{\"status\":\"success\", \"job_identifier\":\"123\"}");
		}


	};
}