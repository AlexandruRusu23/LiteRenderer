#ifndef LOGGER_H
#define LOGGER_H

#include <string>
#include <fstream>
#include <ctime>

namespace Core
{
	namespace Logging
	{
		enum class LogType : uint16_t
		{
			MESSAGE = 1,
			WARNING,
			ERROR_MESSAGE
		};

		class Logger
		{
		public:
			static void Init();
			static void Close();

			static void Log(std::string message, LogType logType = LogType::MESSAGE);
			static void Log(LogType logType, const char* const format, ...);

		private:
			Logger(void) {}
			~Logger(void) {}

			static void UpdateTimestamp();
			static char* NumberToChar(unsigned int num, int base);

			static std::ofstream	m_outStream;
			static __time64_t		m_currentTimestamp;
			static struct tm		m_currentTime;
			static char				m_currentTimeFormatted[26];
		};
	}
}

using namespace Core::Logging;

#endif // !LOGGER_H


