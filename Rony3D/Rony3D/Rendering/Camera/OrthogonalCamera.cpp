#include "OrthogonalCamera.h"

using namespace Rendering::Camera;

OrthogonalCamera::OrthogonalCamera()
{
	m_viewMatrix = glm::mat4(1.0f);
}

OrthogonalCamera::~OrthogonalCamera()
{

}

void OrthogonalCamera::UpdateView()
{

}

glm::mat4 OrthogonalCamera::GetViewMatrix() const
{
	return m_viewMatrix;
}

void OrthogonalCamera::KeyPressed(const unsigned char key)
{

}

void OrthogonalCamera::MousePressed(int button, int state, int x, int y)
{

}

void OrthogonalCamera::MouseMove(int x, int y)
{

}
