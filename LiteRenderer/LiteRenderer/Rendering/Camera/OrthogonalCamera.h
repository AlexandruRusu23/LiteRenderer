#ifndef ORTHOGONAL_CAMERA_H
#define ORTHOGONAL_CAMERA_H

#include "Rendering\ICamera.h"

namespace Rendering
{
	namespace Camera
	{
		class OrthogonalCamera : public ICamera
		{
		public:
			OrthogonalCamera();
			~OrthogonalCamera();

			virtual void UpdateView();

			virtual glm::mat4 GetViewMatrix() const;

			virtual void KeyPressed(const unsigned char key);
			virtual void MousePressed(int button, int state, int x, int y);
			virtual void MouseMove(int x, int y);

		private:
			glm::mat4 m_viewMatrix;
		};
	}
}

#endif // !ORTHOGONAL_CAMERA_H
