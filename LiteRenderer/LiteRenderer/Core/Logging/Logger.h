#ifndef LOGGING_LOGGER_H
#define LOGGING_LOGGER_H

#include <string>
#include <bitset>
#include <fstream>

namespace LiteRenderer
{
	namespace Core
	{
		namespace Logging
		{
			class Logger
			{
			public:
				Logger(void) = delete;
				~Logger(void) = delete;
				Logger(Logger& logger) = delete;
				Logger& operator=(const Logger& logger) = delete;

				static void Init(std::string filename = "LiteRenderer.log", unsigned int flags = LOG_ALL | PRINT_BOTH);
				static void ChangeFlags(unsigned int flags);
				static unsigned int GetFlags();
				static void Close();

				static void Log(const char* const format, ...);

				static const unsigned int LOG_HIGH_ERRORS = 1 << 0;
				static const unsigned int LOG_MEDIUM_ERRORS = 1 << 1;
				static const unsigned int LOG_LOW_ERRORS = 1 << 2;
				static const unsigned int LOG_NOTIFICATIONS = 1 << 3;
				static const unsigned int LOG_ALL = (1 << 4) - 1;
				static const unsigned int PRINT_CONSOLE = 1 << 4;
				static const unsigned int STORE_IN_FILE = 1 << 5;
				static const unsigned int PRINT_BOTH = PRINT_CONSOLE | STORE_IN_FILE;

			private:
				static std::ofstream	m_outStream;
				static std::bitset<8>	m_logFlags;
			};
		}
	}
}

using namespace LiteRenderer::Core::Logging;

#endif // !LOGGING_LOGGER_H

