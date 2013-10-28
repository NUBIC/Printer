#include "stdafx.h"
#include "CppUnitTest.h"
#include "Cli.h"
#include <tchar.h>
#include <iostream>
#include <string>
#include <wchar.h>
#include "SpoolStatus.h"
#include "FakeSpooler.h"
#include "ExceptionalSpooler.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

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

		TEST_METHOD(TestFileNotFound)
		{
			_TCHAR *argv[] = {
				L"Printer",
				L"hp-printer",
				L"invalid.txt"
			};
			runCli(argv, 3);
			expectOutput(L"Failed to open the file 'invalid.txt'");
		}

		TEST_METHOD(TestSpoolSuccess)
		{
			_TCHAR *argv[] = {
				L"Printer",
				L"hp-printer",
				L"../Printer_Test/valid.txt"
			};
			runCli(argv, 3, new FakeSpooler());
			expectOutput(L"Successfully spooled '../Printer_Test/valid.txt' to printer 'hp-printer'\nJob identifier is '123'");
		}

		TEST_METHOD(TestSpoolSuccessWithJsonSwitch) {
			_TCHAR *argv[] = {
				L"Printer",
				L"/json",
				L"hp-printer",
				L"../Printer_Test/valid.txt"
			};
			runCli(argv, 4, new FakeSpooler());
			expectOutput( L"{\"status\":\"success\", \"job_id\":123}");
		}

		TEST_METHOD(TestSpoolFailureWithJsonSwitch) {
			_TCHAR *argv[] = {
				L"Printer",
				L"/json",
				L"hp-printer",
				L"../Printer_Test/valid.txt"
			};
			runCli(argv, 4, new ExceptionalSpooler());
			expectOutput( L"{\"status\":\"failure\", \"message\":\"I am exceptional!\"}");
		}

		TEST_METHOD(TestBadFileWithJsonSwitch) {
			_TCHAR *argv[] = {
				L"Printer",
				L"/json",
				L"hp-printer",
				L"invalid.txt"
			};
			runCli(argv, 4, new FakeSpooler());
			expectOutput( L"{\"status\":\"failure\", \"message\":\"Failed to open the file 'invalid.txt'\"}");
		}

		TEST_METHOD(TestIsJobSwitch) {
			Cli* s = new Cli(0,NULL);
			s->isJobSwitch(L"/job:123");
		}

		TEST_METHOD(TestExtractJobIdFromJobSwitch) {
			Cli* s = new Cli(0,NULL);
			DWORD actual = s->extractJobIdFromJobSwitch(L"/job:123");
			Assert::AreEqual((DWORD) 123, actual);
		}

		TEST_METHOD(TestExtractJobIdFromJobSwitchWhenNonNumericJobId) {
			Cli* s = new Cli(0,NULL);
			DWORD actual = s->extractJobIdFromJobSwitch(L"/job:123XXX");
			Assert::AreEqual((DWORD) 123, actual);
		}

		TEST_METHOD(TestExtractJobIdFromJobSwitchWhenMissingJobId) {
			Cli* s = new Cli(0,NULL);
			DWORD actual = s->extractJobIdFromJobSwitch(L"/job");
			Assert::AreEqual((DWORD) 0, actual);
		}

		/* Helper Methods */

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

		static void runCli(_TCHAR* argv[], int argc) {
			buffer.clear();
			old = std::wcout.rdbuf(buffer.rdbuf());
			Cli *c = new Cli(argc, argv);
			c->run();
		}

		static void runCli(_TCHAR* argv[], int argc, SpoolerInterface* s) {
			buffer.clear();
			old = std::wcout.rdbuf(buffer.rdbuf());
			Cli *c = new Cli(argc, argv);
			c->setSpooler(s);
			c->run();
		}

	};
}