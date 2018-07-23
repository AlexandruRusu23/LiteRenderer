#include "Timer.h"

uint64_t Timer::m_currentTimeMS(0);
uint64_t Timer::m_deltaTimeMS(0);

void Timer::Init()
{
	m_currentTimeMS = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
}

void Timer::Update()
{
	uint64_t lastTimeMS = m_currentTimeMS;
	m_currentTimeMS = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();

	m_deltaTimeMS = m_currentTimeMS - lastTimeMS;
}

float Timer::GetDeltaTime()
{
	return m_deltaTimeMS / 1000.0f;
}

uint64_t Timer::GetDeltaTimeMS()
{
	return m_deltaTimeMS;
}
