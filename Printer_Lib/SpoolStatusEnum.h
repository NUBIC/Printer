#pragma once

#include <stdexcept>

namespace SpoolStatusEnum {
	enum class Enum {
		SPOOLING, 
		FAILURE
	};

	LPTSTR toString(Enum e);
}