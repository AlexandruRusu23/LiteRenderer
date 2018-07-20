#ifndef LOGGER_H
#define LOGGER_H

#include <string>
#include <fstream>
#include <ctime>

namespace Core
{
	namespace Logging
	{
		class Logger
		{
		public:
			static void Init(std::string filename = "Rony3D.log");
			static void Close();

			static void Log(const char* const format, ...);

		private:
			Logger(void) {}
			~Logger(void) {}

			static std::ofstream	m_outStream;
		};
	}
}

using namespace Core::Logging;

#endif // !LOGGER_H
