#include "Engine.h"
#include "Rendering\Models\CubeIndex.h"

using namespace Rony3D;
using namespace Rendering;
using namespace Models;

static const std::string k_cubeShader = "cubeShader";

int main(int argc, char **argv)
{
	Engine* engine = new Engine();
	engine->Init();

	engine->GetShaderManager()->CreateProgram(k_cubeShader.c_str(),
		"Shaders/VertexShader.glsl",
		"Shaders/FragmentShader.glsl");

	CubeIndex* cubeIndex = new CubeIndex();
	cubeIndex->SetProgram(engine->GetShaderManager()->GetShader(k_cubeShader.c_str()));
	cubeIndex->Create();

	engine->GetModelsManager()->SetModel("cubeIndex", cubeIndex);

	engine->Run();

	delete engine;
	return 0;
}