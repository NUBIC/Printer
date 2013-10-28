#include "stdafx.h"
#include "SpoolStatusEnum.h"

namespace SpoolStatusEnum {
	LPTSTR toString(Enum e) {
		switch (e) {
		case Enum::SPOOLING:
			return L"spooling";
			break;
		case Enum::FAILURE:
			return L"failure";
			break;
		default:
			throw std::runtime_error("Unknown SpoolStatusEnum");
			break;
		}
	}
}