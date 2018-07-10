#ifndef CUBEINDEX_H
#define CUBEINDEX_H

#include "Model.h"
#include <chrono>

namespace Rendering
{
	namespace Models
	{
		class CubeIndex : public Model
		{
		public:
			CubeIndex();
			~CubeIndex();

			void Create();
			virtual void Draw(const glm::mat4& projectionMatrix, const glm::mat4& viewMatrix) override final;

			virtual void Update() override final;

		private:
			glm::vec3 m_rotation;
			glm::vec3 m_rotationSpeed;
			glm::vec3 m_translate;
			glm::mat4 m_translateMatrix;
			std::chrono::milliseconds m_timer;
		};
	}
}

#endif
