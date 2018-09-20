#ifndef MODELS_CUBETEXTURE_H
#define MODELS_CUBETEXTURE_H

#include "Model.h"

namespace LiteRenderer
{
	namespace Rendering
	{
		namespace Models
		{
			class CubeTexture : public Model
			{
			public:
				CubeTexture();
				~CubeTexture();

				void Create();

				virtual void Update() override final;
				virtual void Draw(const glm::mat4& projectionMatrix, const glm::mat4& viewMatrix) override final;

			private:
				static const float PI; // = 3.14159265f;

				glm::vec3					m_rotation;
				glm::vec3					m_rotationSpeed;
				glm::vec3					m_rotationSin;
				glm::vec3					m_translate;
				glm::mat4					m_translateMatrix;
			};
		}
	}
}

#endif // !MODELS_CUBETEXTURE_H

