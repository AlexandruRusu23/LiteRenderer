#include "Engine.h"
#include "Rendering/Models/CubeTexture.h"

int main(int argc, char **argv)
{
	RenderEngine::Engine* engine = new RenderEngine::Engine();
	engine->Init(argc, argv);

	engine->GetShaderManager()->CreateProgram("texturedCubeShader",
		"Assets/VertexShader.glsl",
		"Assets/FragmentShader.glsl");

	for (int i = 0; i < 5; i++)
	{
		Rendering::Models::CubeTexture* cubeTexture = new Rendering::Models::CubeTexture();
		cubeTexture->SetProgram(engine->GetShaderManager()->GetShader("texturedCubeShader")->GetProgramId());
		cubeTexture->Create();

		unsigned int textureId = engine->GetTextureLoader()->LoadTexture("Textures/Crate.bmp", 256, 256);
		cubeTexture->AddTexture("CrateTexture", textureId);
		cubeTexture->SetCurrentTextures({textureId});

		engine->GetModelsManager()->SetModel("boxModel" + std::to_string(i), cubeTexture);
	}

	engine->Run();

	delete engine;

	return 0;
}
