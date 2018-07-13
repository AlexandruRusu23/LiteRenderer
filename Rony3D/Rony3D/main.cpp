#include "Engine.h"
#include "Rendering\Models\CubeTexture.h"

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

/*This source code copyrighted by Lazy Foo' Productions (2004-2015)
and may not be redistributed without written permission.*/

//Using SDL and standard IO
//#include <sdl\SDL.h>
//#include <stdio.h>
//
//int main(int argc, char** args)
//{
//	//Screen dimension constants
//	const int SCREEN_WIDTH = 640;
//	const int SCREEN_HEIGHT = 480;
//	//The window we'll be rendering to
//	SDL_Window* window = NULL;
//
//	//The surface contained by the window
//	SDL_Surface* screenSurface = NULL;
//
//	//Initialize SDL
//	if (SDL_Init(SDL_INIT_VIDEO) < 0)
//	{
//		printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
//	}
//	else
//	{
//		//Create window
//		window = SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
//		if (window == NULL)
//		{
//			printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
//		}
//		else
//		{
//			//Get window surface
//			screenSurface = SDL_GetWindowSurface(window);
//
//			//Fill the surface white
//			SDL_FillRect(screenSurface, NULL, SDL_MapRGB(screenSurface->format, 0x0, 0xFF, 0xFF));
//
//			//Update the surface
//			SDL_UpdateWindowSurface(window);
//
//			//Wait two seconds
//			SDL_Delay(2000);
//		}
//	}
//
//	//Destroy window
//	SDL_DestroyWindow(window);
//
//	//Quit SDL subsystems
//	SDL_Quit();
//
//	return 0;
//}
