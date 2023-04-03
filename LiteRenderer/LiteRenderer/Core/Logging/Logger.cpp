#include "Logger.h"

#include <iostream>
#include <ctime>
#include <cstdarg>
#include <assert.h>

using namespace LiteRenderer;
using namespace Core;
using namespace Logging;

static constexpr unsigned int LOGGER_STRING_MAX_LENGTH = 1024;

#ifdef _DEBUG
static constexpr bool DEBUG_MODE_ENABLED = true;
#else
static constexpr bool DEBUG_MODE_ENABLED = false;
#endif

std::ofstream Logger::m_outStream;
std::bitset<8> Logger::m_logFlags;

void Logger::Init(const std::string& filename /* = "LiteRenderer.log" */, uint64_t flags /* = LOG_ALL | PRINT_BOTH */)
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

void Logger::AddFlag(uint64_t flag)
{
	m_logFlags |= flag;
}

void Logger::RemoveFlag(uint64_t flag)
{
	m_logFlags &= ~flag;
}

void Logger::ChangeFlags(uint64_t flags)
{
	m_logFlags.reset();
	m_logFlags |= flags;
}

uint64_t Logger::GetFlags()
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
	auto canPrintConsole = []()
	{ 
		return DEBUG_MODE_ENABLED || (GetFlags() & PRINT_CONSOLE); 
	};
	auto canStoreInFile = []()
	{ 
		return GetFlags() & STORE_IN_FILE; 
	};
	auto skipTimestamp = []()
	{
		return GetFlags() & REMOVE_TIMESTAMP;
	};
	auto skipNewLineLog = []()
	{
		return GetFlags() & NO_NEW_LINE_LOG;
	};

	size_t messageLength = 0;
	char messageBuffer[LOGGER_STRING_MAX_LENGTH];

	va_list args;
	va_start(args, format);
	messageLength = _vsnprintf_s(messageBuffer, LOGGER_STRING_MAX_LENGTH - 1, format, args);
	va_end(args);

	if (!skipTimestamp())
	{
		time_t currentTime = time(nullptr);
		struct tm currentTimeData;
		localtime_s(&currentTimeData, &currentTime);
		char currentTimeFormatted[26];
		if (asctime_s(currentTimeFormatted, 26, &currentTimeData))
		{
			m_outStream << "ERROR : Invalid argument to asctime_s." << std::endl;
			std::cout << "ERROR : Invalid argument to asctime_s." << std::endl;
			assert(false);
			return;
		}
		size_t timeFormattedLength = strlen(currentTimeFormatted);
		if (timeFormattedLength)
			currentTimeFormatted[timeFormattedLength - 1] = ' ';

		if (canStoreInFile())
			m_outStream << currentTimeFormatted;
		if (canPrintConsole())
			std::cout << currentTimeFormatted;
	}

	if (canStoreInFile())
		m_outStream << messageBuffer;
	if (canPrintConsole())
		std::cout << messageBuffer;

	if (!skipNewLineLog())
	{
		if (canStoreInFile())
			m_outStream << std::endl;
		if (canPrintConsole())
			std::cout << std::endl;
	}
}
