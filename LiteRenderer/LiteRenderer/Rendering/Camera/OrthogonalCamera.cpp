#include "OrthogonalCamera.h"

using namespace LiteRenderer;
using namespace Rendering;
using namespace Camera;

OrthogonalCamera::OrthogonalCamera()
{
	m_viewMatrix = glm::mat4(1.0f);
}

OrthogonalCamera::~OrthogonalCamera()
{

}

void OrthogonalCamera::Update()
{

}

void OrthogonalCamera::UpdateView()
{

}

glm::mat4 OrthogonalCamera::GetViewMatrix() const
{
	return m_viewMatrix;
}

void OrthogonalCamera::MousePressed(int button, int state, int x, int y)
{

}

void OrthogonalCamera::MouseMove(int x, int y)
{

}

