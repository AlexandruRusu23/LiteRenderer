#include "PerspectiveCamera.h"

#include "Timer.h"
#include "InputController.h"

using namespace LiteRenderer;
using namespace Rendering;
using namespace Camera;

PerspectiveCamera::PerspectiveCamera()
	: m_keyPitch(0)
	, m_keyYaw(0)
	, m_keyRoll(0)
	, m_cameraQuat({ 0,0,0,0 })
	, m_velocity(10)
{
	m_viewMatrix = glm::mat4(	1.0f, 0.0f, 0.0f, 0.0f,
								0.0f, 1.0f, 0.0f, 0.0f,
								0.0f, 0.0f, 1.0f, 0.0f,
								0.0f, 0.0f, 10.0f, 1.0f);

	m_eyeVector = glm::vec3(0.0f, 0.0f, -10.0f);
}

PerspectiveCamera::~PerspectiveCamera()
{

}

void PerspectiveCamera::Update()
{
	// KEYBOARD UPDATE
	float strafeValue = 0;
	float forwardValue = 0;

	if (Core::Input::InputController::IsNormalKeyPressed(Core::Input::Keys::KEY_S))
		forwardValue += static_cast<float>(m_velocity);

	if (Core::Input::InputController::IsNormalKeyPressed(Core::Input::Keys::KEY_W))
		forwardValue -= static_cast<float>(m_velocity);

	if (Core::Input::InputController::IsNormalKeyPressed(Core::Input::Keys::KEY_A))
		strafeValue -= static_cast<float>(m_velocity);

	if (Core::Input::InputController::IsNormalKeyPressed(Core::Input::Keys::KEY_D))
		strafeValue += static_cast<float>(m_velocity);

	glm::mat4 viewMatrix = GetViewMatrix();	
	glm::vec3 forward(viewMatrix[0][2], viewMatrix[1][2], viewMatrix[2][2]);
	glm::vec3 strafe(viewMatrix[0][0], viewMatrix[1][0], viewMatrix[2][0]);

	m_eyeVector += (-forwardValue * forward + strafeValue * strafe) * Utils::Timer::GetDeltaTime();

	// MOUSE UPDATE
	if (Core::Input::InputController::IsMousePressed() && Core::Input::InputController::IsMouseButtonPressed(Core::Input::MouseButton::RIGHT_CLICK))
	{		
		auto mouseDelta = Core::Input::InputController::GetMousePressedDeltaPosition();
		auto mouseSensitivy = Core::Input::InputController::GetMouseSensitivity();

		m_keyYaw = mouseSensitivy.first * mouseDelta.first;
		m_keyPitch = mouseSensitivy.second * mouseDelta.second;
	}

	UpdateView();
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
