#ifndef CAMERA_ORTHOGONALCAMERA_H
#define CAMERA_ORTHOGONALCAMERA_H

#include "Rendering\ICamera.h"

namespace LiteRenderer
{
	namespace Rendering
	{
		namespace Camera
		{
			class OrthogonalCamera : public ICamera
			{
			public:
				OrthogonalCamera();
				~OrthogonalCamera();

				virtual void Update();
				virtual void UpdateView();

				virtual glm::mat4 GetViewMatrix() const;

				virtual void MousePressed(int button, int state, int x, int y);
				virtual void MouseMove(int x, int y);

			private:
				glm::mat4 m_viewMatrix;
			};
		}
	}
}

#endif // !CAMERA_ORTHOGONALCAMERA_H

