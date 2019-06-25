#pragma once
#include "Logger.h"
#include <string>

#define LOG(sLog)				.Log(std::string(sLog) + " at " __FUNCTION__ + " " __FILE__)
#define CHENG_LOG(sLog)			Locator::ChengLogger LOG(sLog)
#define DEFAULT_LOG(sLog)		Locator::DefaultLogger LOG(sLog)
#define RYAN_LOG(sLog)			Locator::RyanLogger LOG(sLog)
#define KZ_LOG(sLog)			Locator::KZLogger LOG(sLog)
#define LZ_LOG(sLog)			Locator::LZLogger LOG(sLog)

class Locator
{
public:
	enum eLoggerUsers
	{
		DEFAULT,
		CHENG,
		RYAN,
		KZ,
		LZ,
	};
private:
public:
	static Logger DefaultLogger;
	static Logger ChengLogger;
	static Logger RyanLogger;
	static Logger KZLogger;
	static Logger LZLogger;
	Locator();
	~Locator();

	static Logger& GetLogger(eLoggerUsers user);
};
