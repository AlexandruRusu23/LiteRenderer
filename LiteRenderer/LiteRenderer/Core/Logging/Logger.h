#ifndef LOGGING_LOGGER_H
#define LOGGING_LOGGER_H

#include <string>
#include <fstream>
#include <ctime>

namespace LiteRenderer
{
	namespace Core
	{
		namespace Logging
		{
			class Logger
			{
			public:
				static void Init(std::string filename = "LiteRenderer.log");
				static void Close();

				static void Log(const char* const format, ...);

			private:
				Logger(void) {}
				~Logger(void) {}

				static std::ofstream	m_outStream;
			};
		}
	}
}

using namespace LiteRenderer::Core::Logging;

#endif // !LOGGING_LOGGER_H

