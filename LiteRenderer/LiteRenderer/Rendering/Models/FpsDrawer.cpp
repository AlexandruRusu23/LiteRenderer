#include "FpsDrawer.h"

#include <math.h>

#include "Timer.h"

using namespace LiteRenderer;
using namespace Rendering;
using namespace Models;

const float FpsDrawer::TIME_TO_REFRESH = 150.f;

FpsDrawer::FpsDrawer()
	: m_sumDeltaMS(0)
	, m_timeToRefresh(TIME_TO_REFRESH)
{
	m_textObject = Text::TextObject();
	m_textObject.textFontname = "arial";
	m_textObject.textToRender = "0";
	m_textObject.textCoords = { 10, glutGet(GLUT_SCREEN_HEIGHT) - 30 };
	m_textObject.textColor = { 1, 0, 0 };
	m_textObject.textSize = 24;

	using TextLoader = Rendering::Text::TextLoader;
	TextLoader::Instance().LoadFont(m_textObject.textFontname, "Assets/Fonts/Arial.ttf", m_textObject.textSize);
}

FpsDrawer::~FpsDrawer()
{

}

void FpsDrawer::Update()
{
	m_sumDeltaMS += Utils::Timer::GetDeltaTimeMS();

	if (m_sumDeltaMS >= m_timeToRefresh)
	{
		auto fps = static_cast<int>(1000.0f / Utils::Timer::GetDeltaTimeMS());
		m_textObject.textToRender = "FPS " + std::to_string(fps);
		m_sumDeltaMS = 0.0f;
	}
}

void FpsDrawer::ChangeTimeToRefresh(float timeToRefresh)
{
	m_timeToRefresh = timeToRefresh;
}

