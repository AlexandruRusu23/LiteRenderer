#ifndef UTILS_TIMER_H
#define UTILS_TIMER_H

#include <chrono>
#include <cstdint>

namespace LiteRenderer
{
	namespace Utils
	{
		class Timer
		{
		public:
			Timer() = delete;
			~Timer() = delete;
			Timer(Timer& timer) = delete;
			Timer& operator=(const Timer& timer) = delete;

			static void Init();
			static void Update();

			static float GetDeltaTime();

			static uint64_t GetDeltaTimeMS();

		private:
			static uint64_t m_currentTimeMS;
			static uint64_t m_deltaTimeMS;
		};
	}
}

#endif // !UTILS_TIMER_H

