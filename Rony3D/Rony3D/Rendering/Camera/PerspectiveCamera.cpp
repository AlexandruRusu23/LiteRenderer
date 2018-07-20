#include "PerspectiveCamera.h"

#include <freeglut\freeglut.h>

using namespace Rendering::Camera;

PerspectiveCamera::PerspectiveCamera()
	: m_keyPitch(0)
	, m_keyRoll(0)
	, m_keyYaw(0)
	, m_cameraQuat({0,0,0,0})
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

void PerspectiveCamera::KeyPressed(const unsigned char key)
{
	float dx = 0;
	float dz = 0;
	switch (key)
	{
	case 's':
	case 'S':
	{
		dz = 30;
		break;
	}

	case 'w':
	case 'W':
	{
		dz = -30;
		break;
	}
	case 'a':
	case 'A':
	{
		dx = -30;
		break;
	}
	case 'd':
	case 'D':
	{
		dx = 30;
		break;
	}
	default:
		break;
	}

	glm::mat4 mat = GetViewMatrix();
	
	glm::vec3 forward(mat[0][2], mat[1][2], mat[2][2]);
	glm::vec3 strafe(mat[0][0], mat[1][0], mat[2][0]);

	const float speed = 0.008f;
	m_eyeVector += (-dz * forward + dx * strafe) * speed;

	UpdateView();
}

void PerspectiveCamera::MousePressed(int button, int state, int x, int y)
{
	if (state == GLUT_DOWN)
	{
		m_mousePosition.x = static_cast<float>(x);
		m_mousePosition.y = static_cast<float>(y);
	}
}

void PerspectiveCamera::MouseMove(int x, int y)
{
	glm::vec2 mouse_delta = glm::vec2(x, y) - m_mousePosition;

	const float mouseX_Sensitivity = 0.0020f;
	const float mouseY_Sensitivity = 0.0020f;

	m_keyYaw = mouseX_Sensitivity * mouse_delta.x;
	m_keyPitch = mouseY_Sensitivity * mouse_delta.y;

	m_mousePosition = glm::vec2(x, y);
	UpdateView();
}
