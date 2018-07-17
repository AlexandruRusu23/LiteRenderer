#include "Engine.h"
#include "Rendering\Models\CubeTexture.h"

using namespace Rony3D;
using namespace Rendering;
using namespace Models;

int main(int argc, char **argv)
{
	Engine* engine = new Engine();
	engine->Init(argc, argv);

	engine->GetShaderManager()->CreateProgram("cubeShader",
		"Shaders/VertexShader.glsl",
		"Shaders/FragmentShader.glsl");

	CubeTexture* cubeTexture = new CubeTexture();
	cubeTexture->SetProgram(engine->GetShaderManager()->GetShader("cubeShader"));
	cubeTexture->Create();

	unsigned int textureId = engine->GetTextureLoader()->LoadTexture("Textures/Crate.bmp", 256, 256);
	cubeTexture->SetTexture("Create", textureId);

	engine->GetModelsManager()->SetModel("cubeTexture", cubeTexture);

	engine->Run();

	delete engine;

	return 0;
}
