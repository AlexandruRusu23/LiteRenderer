#ifndef PERSPECTIVE_CAMERA_H
#define PERSPECTIVE_CAMERA_H

#include "Rendering/ICamera.h"

namespace Rendering
{
	namespace Camera
	{
		class PerspectiveCamera : public ICamera
		{
		public:
			PerspectiveCamera();
			~PerspectiveCamera();

			virtual void UpdateView();

			virtual glm::mat4 GetViewMatrix() const;

			virtual void KeyPressed(const unsigned char key);
			virtual void MousePressed(int button, int state, int x, int y);
			virtual void MouseMove(int x, int y);

		private:
			glm::mat4 m_viewMatrix;

			glm::vec3 m_eyeVector;
			glm::vec2 m_mousePosition;
			glm::quat m_cameraQuat;

			float m_keyRoll;
			float m_keyPitch;
			float m_keyYaw;
		};
	}
}

#endif // !PERSPECTIVE_CAMERA_H


