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

int Logger::PrintLogs(int iYOffset)
{
	for (unsigned i = 0; i < m_vec_LogList.size(); ++i)
	{
		COORD coord;
		coord.X = 0;
		coord.Y = i + 1 + iYOffset;
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
		LogData log = m_vec_LogList[i];
		WindowData* WinData = WindowData::GetInstance();
		const int WINDOW_LENGTH = (int)WinData->GetConsoleSize().x;
		const int WINDOW_CHAR_LENGTH = WINDOW_LENGTH / (int)WinData->GetFontSize().x;
		iYOffset += log.m_sLog.size() / WINDOW_CHAR_LENGTH;
		// Print
		std::cout << log.m_iNumCalls << "  " << log.m_sLog << '\n';
	}
	return iYOffset;
}