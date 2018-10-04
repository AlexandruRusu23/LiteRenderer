#include "Logger.h"

#include <iostream>
#include <ctime>
#include <cstdarg>
#include <assert.h>

using namespace LiteRenderer;
using namespace Core;
using namespace Logging;

static const unsigned int LOGGER_STRING_MAX_LENGTH = 1024;

#ifdef _DEBUG
static const bool DEBUG_MODE_ENABLED = true;
#else
static const bool DEBUG_MODE_ENABLED = false;
#endif

std::ofstream Logger::m_outStream;
std::bitset<8> Logger::m_logFlags;

void Logger::Init(std::string filename /* = "LiteRenderer.log" */, unsigned int flags /* = LOG_ALL */)
{
	if (m_outStream.is_open())
	{
		assert(false);
		return;
	}

	m_logFlags |= flags;
	m_outStream.open(filename, std::ofstream::out | std::ofstream::app);
	Log("**Logger initialized**\n");
}

void Logger::ChangeFlags(unsigned int flags)
{
	m_logFlags.reset();
	m_logFlags |= flags;
}

unsigned int Logger::GetFlags()
{
	return m_logFlags.to_ulong();
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
		m_outStream << "ERROR : Invalid argument to asctime_s." << std::endl;
		if (DEBUG_MODE_ENABLED)
			std::cout << "ERROR : Invalid argument to asctime_s." << std::endl;
		assert(false);
		return;
	}
	size_t timeFormattedLength = strlen(currentTimeFormatted);
	currentTimeFormatted[timeFormattedLength - 1] = ' ';

	m_outStream << currentTimeFormatted << messageBuffer << std::endl;
	if (DEBUG_MODE_ENABLED)
		std::cout << currentTimeFormatted << messageBuffer << std::endl;
}

