#ifndef MODEL_H
#define MODEL_H

#include <vector>
#include <map>
#include "..\IGameObject.h"

namespace Rendering
{
	namespace Models
	{
		class Model : public IGameObject
		{
		public:
			Model();
			virtual ~Model();
			virtual void Destroy() override;

			virtual void Update() override;
			virtual void Draw() override;
			virtual void Draw(const glm::mat4& projectionMatrix, const glm::mat4& viewMatrix) override;
			
			virtual void SetProgram(GLuint shaderName) override;

			virtual GLuint GetVao() const override;
			virtual const std::vector<GLuint>& GetVbos() const override;

			virtual const GLuint GetTexture(const std::string& textureName) const override;
			virtual void SetTexture(const std::string& textureName, GLuint textureId) override;

		protected:
			GLuint							m_vao;
			GLuint							m_program;
			std::vector<GLuint>				m_vbos;
			std::map<std::string, GLuint>	m_textures;
		};
	}
}

#endif
