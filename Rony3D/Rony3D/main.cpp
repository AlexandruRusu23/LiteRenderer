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

	unsigned int textureId = engine->GetTextureLoader()->LoadTexture("Textures/nebula1.bmp", 256, 256);
	cubeTexture->SetTexture("Create", textureId);

	engine->GetModelsManager()->SetModel("cubeTexture", cubeTexture);

	engine->Run();

	delete engine;
	return 0;
}