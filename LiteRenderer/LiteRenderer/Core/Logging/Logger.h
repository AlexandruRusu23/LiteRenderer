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
			class Logger final
			{
			public:
				Logger() = delete;
				~Logger() = delete;
				Logger(Logger&&) = delete;
				Logger(const Logger&) = delete;
				Logger& operator=(Logger&&) noexcept = delete;
				Logger& operator=(const Logger&) = delete;

				static void Init(const std::string& filename = "LiteRenderer.log", uint64_t flags = LOG_ALL | PRINT_BOTH);
				static void AddFlag(uint64_t flag);
				static void RemoveFlag(uint64_t flag);
				static void ChangeFlags(uint64_t flags);
				[[nodiscard]] static uint64_t GetFlags();
				static void Close();

				static void Log(const char* const format, ...);

				static constexpr uint64_t LOG_HIGH_ERRORS = 1 << 0;
				static constexpr uint64_t LOG_MEDIUM_ERRORS = 1 << 1;
				static constexpr uint64_t LOG_LOW_ERRORS = 1 << 2;
				static constexpr uint64_t LOG_NOTIFICATIONS = 1 << 3;
				static constexpr uint64_t LOG_ALL = (1 << 4) - 1;
				static constexpr uint64_t PRINT_CONSOLE = 1 << 4;
				static constexpr uint64_t STORE_IN_FILE = 1 << 5;
				static constexpr uint64_t PRINT_BOTH = PRINT_CONSOLE | STORE_IN_FILE;
				static constexpr uint64_t REMOVE_TIMESTAMP = 1 << 6;
				static constexpr uint64_t NO_NEW_LINE_LOG = 1 << 7;

			private:
				static std::ofstream	m_outStream;
				static std::bitset<8>	m_logFlags;
			};
		}
	}
}

using namespace LiteRenderer::Core::Logging;

#endif // !LOGGING_LOGGER_H

