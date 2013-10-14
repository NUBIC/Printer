#include "stdafx.h"
#include "CppUnitTest.h"
#include "Spooler.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Printer_Test
{		
	TEST_CLASS(SpoolerTest)
	{
	public:
		
		TEST_METHOD(TestSuccess)
		{
			bool status = Spooler::spool("foo", "bar");
			Assert::IsTrue(status);
		}

	};
}