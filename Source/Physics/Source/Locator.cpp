#include "Locator.h"

Logger Locator::DefaultLogger("DEFAULT", 0x0F);
Logger Locator::ChengLogger("CHENG", 0x0B);

Locator::Locator()
{
}

Locator::~Locator()
{
}

Logger& Locator::GetLogger(eLoggerUsers user)
{
	switch (user)
	{
	case Locator::DEFAULT:
		return DefaultLogger;
		break;
	case Locator::CHENG:
		return ChengLogger;
		break;
	default:
		return DefaultLogger;
		break;
	};
}