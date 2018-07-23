#include "PerspectiveCamera.h"

#include <freeglut\freeglut.h>

#include "Timer.h"

using namespace Rendering::Camera;

PerspectiveCamera::PerspectiveCamera()
	: m_moveCamera(false)
	, m_keyPitch(0)
	, m_keyRoll(0)
	, m_keyYaw(0)
	, m_cameraQuat({ 0,0,0,0 })
	, m_velocity(100)
{
	m_viewMatrix = glm::mat4(	1.0f, 0.0f, 0.0f, 0.0f,
								0.0f, 1.0f, 0.0f, 0.0f,
								0.0f, 0.0f, -1.0f, 0.0f,
								0.0f, 0.0f, 10.0f, 1.0f);

	m_eyeVector = glm::vec3(0.0f, 0.0f, -10.0f);
}

PerspectiveCamera::~PerspectiveCamera()
{

}

void PerspectiveCamera::UpdateView()
{
	glm::quat keyQuat = glm::quat(glm::vec3(m_keyPitch, m_keyYaw, m_keyRoll));
	m_keyPitch = m_keyYaw = m_keyRoll = 0;

	m_cameraQuat = keyQuat * m_cameraQuat;
	m_cameraQuat = glm::normalize(m_cameraQuat);
	glm::mat4 rotateMatrix = glm::mat4_cast(m_cameraQuat);

	glm::mat4 translateMatrix = glm::mat4(1.0f);
	translateMatrix = glm::translate(translateMatrix, -m_eyeVector);

	m_viewMatrix = rotateMatrix * translateMatrix;
}

glm::mat4 PerspectiveCamera::GetViewMatrix() const
{
	return m_viewMatrix;
}

unsigned int PerspectiveCamera::GetCameraVelocity()
{
	return m_velocity;
}

void PerspectiveCamera::SetCameraVelocity(int speed)
{
	m_velocity = speed;
}

void PerspectiveCamera::KeyPressed(const unsigned char key)
{
	float strafeValue = 0;
	float forwardValue = 0;
	switch (key)
	{
	case 's':
	case 'S':
	{
		forwardValue = static_cast<float>(m_velocity);
		break;
	}

	case 'w':
	case 'W':
	{
		forwardValue = -static_cast<float>(m_velocity);
		break;
	}
	case 'a':
	case 'A':
	{
		strafeValue = -static_cast<float>(m_velocity);
		break;
	}
	case 'd':
	case 'D':
	{
		strafeValue = static_cast<float>(m_velocity);
		break;
	}
	default:
		break;
	}

	glm::mat4 mat = GetViewMatrix();
	
	glm::vec3 forward(mat[0][2], mat[1][2], mat[2][2]);
	glm::vec3 strafe(mat[0][0], mat[1][0], mat[2][0]);

	m_eyeVector += (-forwardValue * forward + strafeValue * strafe) * Timer::GetDeltaTime();

	UpdateView();
}

void PerspectiveCamera::MousePressed(int button, int state, int x, int y)
{
	if (state == GLUT_DOWN && button == GLUT_RIGHT_BUTTON)
	{
		m_moveCamera = true;
		m_mousePosition.x = static_cast<float>(x);
		m_mousePosition.y = static_cast<float>(y);
	}
	else
		m_moveCamera = false;
}

void PerspectiveCamera::MouseMove(int x, int y)
{
	if (!m_moveCamera)
		return;

	glm::vec2 mouse_delta = glm::vec2(x, y) - m_mousePosition;

	const float mouseX_Sensitivity = 0.0020f;
	const float mouseY_Sensitivity = 0.0020f;

	m_keyYaw = mouseX_Sensitivity * mouse_delta.x;
	m_keyPitch = mouseY_Sensitivity * mouse_delta.y;

	m_mousePosition = glm::vec2(x, y);
	UpdateView();
}
