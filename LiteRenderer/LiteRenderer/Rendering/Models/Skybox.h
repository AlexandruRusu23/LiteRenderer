#ifndef MODELS_SKYBOX_H
#define MODELS_SKYBOX_H

#include "Model.h"

namespace LiteRenderer
{
	namespace Rendering
	{
		namespace Models
		{
			class Skybox : public Model
			{
			public:
				Skybox();
				~Skybox();

				void Create();

				virtual void Update() override final;
				virtual void Draw(const glm::mat4& projectionMatrix, const glm::mat4& viewMatrix) override final;
			};
		}
	}
}

#endif

