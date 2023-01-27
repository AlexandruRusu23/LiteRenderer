#include "Engine.h"
#include "Rendering/Models/CubeTexture.h"
#include "Rendering/Models/Skybox.h"
#include "Rendering/Models/FpsDrawer.h"
#include "Rendering/Text/TextModel.h"

using namespace LiteRenderer;

static const std::vector<std::string> skyboxTextures =
{
	"Assets/Textures/Skyboxes/Cloudtop/cloudtop_rt.bmp",
	"Assets/Textures/Skyboxes/Cloudtop/cloudtop_lf.bmp",
	"Assets/Textures/Skyboxes/Cloudtop/cloudtop_up.bmp",
	"Assets/Textures/Skyboxes/Cloudtop/cloudtop_dn.bmp",
	"Assets/Textures/Skyboxes/Cloudtop/cloudtop_ft.bmp",
	"Assets/Textures/Skyboxes/Cloudtop/cloudtop_bk.bmp"
};

static const std::vector<std::string> skyboxBlueSkyTextures =
{
	"Assets/Textures/Skyboxes/Bluesky/bluesky_rt.bmp",
	"Assets/Textures/Skyboxes/Bluesky/bluesky_lf.bmp",
	"Assets/Textures/Skyboxes/Bluesky/bluesky_up.bmp",
	"Assets/Textures/Skyboxes/Bluesky/bluesky_dn.bmp",
	"Assets/Textures/Skyboxes/Bluesky/bluesky_ft.bmp",
	"Assets/Textures/Skyboxes/Bluesky/bluesky_bk.bmp"
};

int main(int argc, char **argv)
{
	LiteRenderer::Engine* engine = new LiteRenderer::Engine();
	engine->Init(argc, argv);

	// CUBES
	engine->GetShaderManager()->CreateProgram("texturedCubeShader",
		"Assets/Shaders/CubeTexturedVertexShader.glsl",
		"Assets/Shaders/CubeTexturedFragmentShader.glsl");

	for (int i = 0; i < 5; i++)
	{
		Rendering::Models::CubeTexture* cubeTexture = new Rendering::Models::CubeTexture();
		cubeTexture->SetProgram(engine->GetShaderManager()->GetShader("texturedCubeShader")->GetProgramId());
		cubeTexture->Create();

		unsigned int textureId = engine->GetTextureLoader()->LoadTexture("Assets/Textures/Test/Crate.bmp");
		cubeTexture->AddTexture("CrateTexture", textureId);
		cubeTexture->SetCurrentTextures({textureId});

		engine->GetModelsManager()->SetModel("boxModel" + std::to_string(i), cubeTexture);
	}

	// TEXT
	engine->GetShaderManager()->CreateProgram("textShader",
		"Assets/Shaders/textRenderVertexShader.glsl",
		"Assets/Shaders/textRenderFragmentShader.glsl");

	Rendering::Text::TextObject textObject;
	textObject.textFontname = "raleway";
	textObject.textToRender = "LiteRenderer | Made by Alexandru Rusu";
	textObject.textCoords = { 10, 10 };
	textObject.textColor = { 1, 0, 0 };
	textObject.textSize = 24;

	using TextLoader = Rendering::Text::TextLoader;
	TextLoader::Instance().LoadFont(textObject.textFontname, "Assets/Fonts/Raleway-Medium.ttf", textObject.textSize);

	Rendering::Text::TextModel* textModel = new Rendering::Text::TextModel();
	textModel->SetProgram(engine->GetShaderManager()->GetShader("textShader")->GetProgramId());
	textModel->Create();
	textModel->SetTextObject(textObject);

	engine->GetModelsManager()->SetModel("textModel", textModel);

	// FPS
	Rendering::Models::FpsDrawer *fpsModel = new Rendering::Models::FpsDrawer();
	fpsModel->SetProgram(engine->GetShaderManager()->GetShader("textShader")->GetProgramId());
	fpsModel->Create();
	engine->GetModelsManager()->SetModel("textFPS", fpsModel);

	// SKYBOX
	engine->GetShaderManager()->CreateProgram("SkyboxShader",
		"Assets/Shaders/skyboxVertexShader.glsl",
		"Assets/Shaders/skyboxFragmentShader.glsl"
	);

	Rendering::Models::Skybox* skybox = new Rendering::Models::Skybox();
	skybox->SetProgram(engine->GetShaderManager()->GetShader("SkyboxShader")->GetProgramId());
	skybox->Create();

	unsigned int textureId = engine->GetTextureLoader()->LoadCubemapTexture(skyboxBlueSkyTextures);
	skybox->AddTexture("SkyboxTexture", textureId);
	skybox->SetCurrentTextures({ textureId });
	
	engine->GetModelsManager()->SetModel("skybox", skybox);

	engine->Run();

	delete engine;

	return 0;
}

