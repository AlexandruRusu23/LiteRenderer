#ifndef ICAMERA_H
#define ICAMERA_H

#include "VertexFormat.h"

namespace Rendering
{
	class ICamera
	{
	public:
		virtual ~ICamera() = 0;

		virtual void UpdateView() = 0;

		virtual glm::mat4 GetViewMatrix() const = 0;
		
		virtual void KeyPressed(const unsigned char key) = 0;
		virtual void MousePressed(int button, int state, int x, int y) = 0;
		virtual void MouseMove(int x, int y) = 0;
	};

	inline ICamera::~ICamera()
	{

	}
}

#endif // !ICAMERA_H

