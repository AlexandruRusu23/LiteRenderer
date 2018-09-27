#ifndef RENDERING_ICAMERA_H
#define RENDERING_ICAMERA_H

#include "VertexFormat.h"

namespace LiteRenderer
{
	namespace Rendering
	{
		class ICamera
		{
		public:
			virtual ~ICamera() = 0;

			virtual void Update() = 0;
			virtual void UpdateView() = 0;

			virtual glm::mat4 GetViewMatrix() const = 0;

			virtual unsigned int GetCameraVelocity() = 0;
			virtual void SetCameraVelocity(int speed) = 0;
		};

		inline ICamera::~ICamera()
		{

		}
	}
}

#endif // !RENDERING_ICAMERA_H

