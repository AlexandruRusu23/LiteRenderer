#include "Engine.h"
#include "Rendering/Models/CubeTexture.h"

int main(int argc, char **argv)
{
	RenderEngine::Engine* engine = new RenderEngine::Engine();
	engine->Init(argc, argv);

	engine->GetShaderManager()->CreateProgram("cubeShader",
		"Assets/VertexShader.glsl",
		"Assets/FragmentShader.glsl");

	Rendering::Models::CubeTexture* cubeTexture = new Rendering::Models::CubeTexture();
	cubeTexture->SetProgram(engine->GetShaderManager()->GetShader("cubeShader")->GetProgramId());
	cubeTexture->Create();

	unsigned int textureId = engine->GetTextureLoader()->LoadTexture("Textures/Crate.bmp", 256, 256);
	cubeTexture->SetTexture("Create", textureId);

	engine->GetModelsManager()->SetModel("cubeTexture", cubeTexture);

	engine->Run();

	delete engine;

	return 0;
}
