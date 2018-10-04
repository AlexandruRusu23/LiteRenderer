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
				static void Init(std::string filename = "LiteRenderer.log", unsigned int flags = LOG_ALL);
				static void ChangeFlags(unsigned int flags);
				static unsigned int GetFlags();
				static void Close();

				static void Log(const char* const format, ...);

				static const unsigned int LOG_HIGH_ERRORS = 1 << 0;
				static const unsigned int LOG_MEDIUM_ERRORS = 1 << 1;
				static const unsigned int LOG_LOW_ERRORS = 1 << 2;
				static const unsigned int LOG_NOTIFICATIONS = 1 << 3;
				static const unsigned int LOG_ALL = (1 << 4) - 1;

			private:
				Logger(void) {}
				~Logger(void) {}

				static std::ofstream	m_outStream;
				static std::bitset<8>	m_logFlags;
			};
		}
	}
}

using namespace LiteRenderer::Core::Logging;

#endif // !LOGGING_LOGGER_H

