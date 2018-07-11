#include "Engine.h"
#include "Rendering\Models\CubeTexture.h"

#include <soil\SOIL.h>

using namespace Rony3D;
using namespace Rendering;
using namespace Models;

static const std::string k_cubeShader = "cubeShader";

int main(int argc, char **argv)
{
	Engine* engine = new Engine();
	engine->Init(argc, argv);

	engine->GetShaderManager()->CreateProgram(k_cubeShader.c_str(),
		"Shaders/VertexShader.glsl",
		"Shaders/FragmentShader.glsl");

	CubeTexture* cubeTexture = new CubeTexture();
	cubeTexture->SetProgram(engine->GetShaderManager()->GetShader(k_cubeShader.c_str()));
	cubeTexture->Create();

	unsigned int texture = engine->GetTextureLoader()->LoadTexture("Textures/bamboo.bmp", 256, 256);
	//unsigned int textureId = SOIL_load_OGL_texture("Textures/nebula1.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS);
	cubeTexture->SetTexture("Create", texture);

	engine->GetModelsManager()->SetModel("cubeTexture", cubeTexture);

	engine->Run();

	delete engine;
	return 0;
}