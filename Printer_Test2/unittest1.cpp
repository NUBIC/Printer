#include "stdafx.h"
#include "CppUnitTest.h"
#include "Printer.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Printer_Test2
{		
	TEST_CLASS(UnitTest1)
	{
	public:
		
		TEST_METHOD(TestMethod1)
		{
			Assert::IsFalse(false);
			Printer *p = new Printer();
		}

	};
}