#include "Logger.h"

Logger::Logger()
{
}

Logger::~Logger()
{
}

void Logger::Log(std::string s)
{
	// check if exists
	for (unsigned i = 0; i < m_vec_LogList.size(); i++)
	{
		if (m_vec_LogList[i].m_sLog == s)
		{
			++m_vec_LogList[i].m_iNumCalls;
			return;
		}
	}
	m_vec_LogList.push_back(LogData(s));
}

void Logger::PrintLogs()
{
	for (unsigned i = 0; i < m_vec_LogList.size(); ++i)
	{
		COORD coord;
		coord.X = 0;
		coord.Y = i + 4;
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
		LogData log = m_vec_LogList[i];
		if (log.m_sLog.size() >= 1000)
		{
			// Do something
		}
		// Print
		std::cout << log.m_iNumCalls << "  " << log.m_sLog << std::endl;
	}
}