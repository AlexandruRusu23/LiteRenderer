#ifndef DRAWINGSHADER_H
#define DRAWINGSHADER_H

#include "ShaderObject.h"

namespace Rendering
{
	namespace Shaders
	{
		class DrawingShader : public ShaderObject
		{
		public:
			DrawingShader(const std::string& shaderName, 
				GLuint programId,
				GLuint vertexShaderId,
				GLuint fragmentShaderId,
				GLuint geometryShaderId = 0);
			~DrawingShader();

			GLuint GetVertexShader() const;
			GLuint GetFragmentShader() const;
			GLuint GetGeometryShader() const;

			void SetVertexShaderFilename(const std::string& filename);
			void SetFragmentShaderFilename(const std::string& filename);
			void SetGeometryShaderFilename(const std::string& filename);

		protected:
			std::string m_vertexShaderFilename;
			std::string m_fragmentShaderFilename;
			std::string m_geometryShaderFilename;

			GLuint		m_vertexShaderId;
			GLuint		m_fragmentShaderId;
			GLuint		m_geometryShaderId;
		};
	}
}

#endif // !DRAWINGSHADER_H

