#include "Logger.h"

#include <iostream>
#include <cstdio>
#include <cstdarg>

using namespace Core::Logging;

static const unsigned int LOGGER_STRING_MAX_LENGTH = 1024;

std::ofstream Logger::m_outStream;

void Logger::Init(std::string filename /* = "Rony3D.log" */)
{
	if (m_outStream.is_open())
	{
		_ASSERT(false);
		return;
	}

	m_outStream.open(filename, std::ofstream::out | std::ofstream::app);
	Log("**Logger initialized**\n");
}

void Logger::Close()
{
	Log("**Logger uninitialized**\n");
	m_outStream.close();
}

void Logger::Log(const char* const format, ...)
{
	size_t messageLength = 0;
	char messageBuffer[LOGGER_STRING_MAX_LENGTH];
	memset(messageBuffer, 0, sizeof(messageBuffer));

	va_list args;
	va_start(args, format);
	messageLength = _vsnprintf_s(messageBuffer, LOGGER_STRING_MAX_LENGTH - 1, format, args);
	messageBuffer[messageLength] = '\0';
	va_end(args);

	time_t currentTime = time(nullptr);
	struct tm currentTimeData;
	localtime_s(&currentTimeData, &currentTime);
	char currentTimeFormatted[26];
	if (asctime_s(currentTimeFormatted, 26, &currentTimeData))
	{
		_ASSERT(false);
		m_outStream << "ERROR : Invalid argument to asctime_s." << std::endl;
		return;
	}
	size_t timeFormattedLength = strlen(currentTimeFormatted);
	currentTimeFormatted[timeFormattedLength - 1] = ' ';

	m_outStream << currentTimeFormatted << messageBuffer << std::endl;
	std::cout << currentTimeFormatted << messageBuffer << std::endl;
}
