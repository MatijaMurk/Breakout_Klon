#pragma once
#include "SDL.h"
#include "SDL_image.h"
#include "SDL_ttf.h"
#include <stdio.h>
#include <string>


class Graphics
{
public:
	static const int ScreenWidth = 1200;
	static const int ScreenHeight = 900;
	const char* WindowName = "BREJ KAUT";

private:
	static Graphics* instance;
	static bool initialized;
	
	SDL_Window* window;
	SDL_Surface* backBuffer;

	SDL_Renderer* mRenderer;

public:

	static Graphics* Instance();
	static void Release();
	static bool Initialized();

	SDL_Texture* LoadTexture(std::string path);

	SDL_Texture* CreateTextTexture(TTF_Font* font, std::string text, SDL_Color color);

	void ClearBackBuffer();

	void DrawTexture(SDL_Texture* tex,SDL_Rect* rend=NULL, float angle=0.0f, SDL_RendererFlip flip=SDL_FLIP_NONE);

	void Render();

private:

	Graphics();
	~Graphics();

	bool Init();

};

