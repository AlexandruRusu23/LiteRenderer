#ifndef CAMERA_PERSPECTIVECAMERA_H
#define CAMERA_PERSPECTIVECAMERA_H

#include "Rendering/ICamera.h"

namespace LiteRenderer
{
	namespace Rendering
	{
		namespace Camera
		{
			class PerspectiveCamera : public ICamera
			{
			public:
				PerspectiveCamera();
				~PerspectiveCamera();

				virtual void Update();
				virtual void UpdateView();

				virtual glm::mat4 GetViewMatrix() const;

				virtual unsigned int GetCameraVelocity();
				virtual void SetCameraVelocity(int speed);

			private:
				glm::mat4 m_viewMatrix;

				glm::vec3 m_eyeVector;
				glm::quat m_cameraQuat;

				float m_keyPitch;
				float m_keyYaw;
				float m_keyRoll;

				int m_velocity;
			};
		}
	}
}

#endif // !CAMERA_PERSPECTIVECAMERA_H

