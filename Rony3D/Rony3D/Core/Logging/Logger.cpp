#include "Logger.h"

#include <iostream>
#include <iomanip>
#include <cstdio>
#include <cstdarg>

using namespace Core::Logging;

std::ofstream Logger::m_outStream;
__time64_t Logger::m_currentTimestamp;
struct tm Logger::m_currentTime;
char Logger::m_currentTimeFormatted[26];

void Logger::Init()
{
	m_outStream.open("Rony3D.log", std::ofstream::out | std::ofstream::app);
	Log("*********************Logger initialized***********************\n");
}

void Logger::Close()
{
	Log("\n\n*******************End of logging***********************\n\n");
	m_outStream.close();
}

void Logger::Log(std::string message, LogType logType /* = LogType::MESSAGE */)
{
	if (!m_outStream.good())
	{
		_ASSERT(false);
		return;
	}

	UpdateTimestamp();
	switch (logType)
	{
	case LogType::MESSAGE:
		m_outStream << std::string(m_currentTimeFormatted) + message << std::endl;
		std::cout << m_currentTimeFormatted << message << std::endl;
		break;
	case LogType::WARNING:
		m_outStream << std::string(m_currentTimeFormatted) + "-- Warning -- " + message << std::endl;
		std::cout << m_currentTimeFormatted << "-- Warning -- " << message << std::endl;
		break;
	case LogType::ERROR_MESSAGE:
		m_outStream << m_currentTimeFormatted << "!! ERROR !! " << message << std::endl;
		std::cout << m_currentTimeFormatted << "!! ERROR !! " << message << std::endl;
		break;
	}
}

void Logger::Log(LogType logType, const char* const format, ...)
{
	std::string parsedArgs;
	const char* traverse;
	int alphaNumValue;
	char *stringValue;

	va_list arg;
	va_start(arg, format);

	for (traverse = format; *traverse != '\0'; traverse++)
	{
		while (*traverse != '%')
		{
			parsedArgs += *traverse;
			traverse++;
		}

		traverse++;
		switch (*traverse)
		{
		case 'c':
			alphaNumValue = va_arg(arg, int); //Fetch char argument
			parsedArgs += alphaNumValue;
			break;

		case 'd':
			alphaNumValue = va_arg(arg, int); //Fetch Decimal/Integer argument
			if (alphaNumValue < 0)
			{
				alphaNumValue = -alphaNumValue;
				parsedArgs += '-';
			}
			parsedArgs += NumberToChar(alphaNumValue, 10);
			break;

		case 'o':
			alphaNumValue = va_arg(arg, unsigned int); //Fetch Octal representation
			parsedArgs += NumberToChar(alphaNumValue, 8);
			break;

		case 's':
			stringValue = va_arg(arg, char *); //Fetch string
			parsedArgs += stringValue;
			break;

		case 'x':
			alphaNumValue = va_arg(arg, unsigned int); //Fetch Hexadecimal representation
			parsedArgs += NumberToChar(alphaNumValue, 16);
			break;
		}
	}
	va_end(arg);

	Log(parsedArgs, logType);
}

void Logger::UpdateTimestamp()
{
	_time64(&m_currentTimestamp);
	localtime_s(&m_currentTime, &m_currentTimestamp);
	if (asctime_s(m_currentTimeFormatted, 26, &m_currentTime))
	{
		m_outStream << "ERROR : Invalid argument to asctime_s." << std::endl;
		return;
	}

	size_t timeFormattedLength = strlen(m_currentTimeFormatted);
	m_currentTimeFormatted[timeFormattedLength - 1] = ' ';
}

char* Logger::NumberToChar(unsigned int num, int base)
{
	static char Representation[] = "0123456789ABCDEF";
	static char buffer[50];
	char *ptr;

	ptr = &buffer[49];
	*ptr = '\0';

	do
	{
		*--ptr = Representation[num%base];
		num /= base;
	} while (num != 0);

	return(ptr);
}
