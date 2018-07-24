#ifndef RENDERING_IGAMEOBJECT_H
#define RENDERING_IGAMEOBJECT_H

#include <set>
#include <vector>
#include <map>

#include <glew/glew.h>
#include <freeglut/freeglut.h>

#include "VertexFormat.h"
#include "Texture/TextureLoader.h"

namespace LiteRenderer
{
	namespace Rendering
	{
		class IGameObject
		{
		public:
			virtual ~IGameObject() = 0;

			virtual void Update() = 0;
			virtual void Draw() = 0;
			virtual void Draw(const glm::mat4& projectionMatrix, const glm::mat4& viewMatrix) = 0;
			virtual void SetProgram(GLuint shaderName) = 0;
			virtual void Destroy() = 0;

			virtual GLuint GetVao() const = 0;
			virtual const std::vector<GLuint>& GetVbos() const = 0;

			virtual const GLuint GetTexture(const std::string& textureName) const = 0;
			virtual void AddTexture(const std::string& textureName, GLuint textureId) = 0;
			virtual std::set<GLuint> const &GetCurrentTextures() const = 0;
			virtual void SetCurrentTextures(const std::set<GLuint>& textures) = 0;
		};

		inline IGameObject::~IGameObject()
		{

		}
	}
}

#endif // !RENDERING_IGAMEOBJECT_H

