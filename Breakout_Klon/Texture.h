#pragma once

#include "GameObject.h"
#include "AssetManager.h"

class Texture : public GameObject
{
protected:
	SDL_Texture* mTex;
	Graphics* mGraphics;

	int mWidth;
	int mHeight;

	SDL_Rect mRenderRect;


public:

	Texture(std::string filename);
	Texture(std::string text, std::string fontpath, int size, SDL_Color color);
	~Texture();

	Vector2 ScaledDimensions();

	virtual void Render();

};

