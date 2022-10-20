#include "Texture.h"

Texture::Texture(std::string filename) {

	mGraphics = Graphics::Instance();

	mTex = AssetManager::Instance()->GetTexture(filename);

	SDL_QueryTexture(mTex, NULL, NULL, &mWidth, &mHeight);

	mRenderRect.w = mWidth;
	mRenderRect.h = mHeight;
}

Texture::Texture(std::string text, std::string fontPath, int size, SDL_Color color) {

	mGraphics = Graphics::Instance();

	mTex = AssetManager::Instance()->GetText(text,fontPath, size, color);

	SDL_QueryTexture(mTex, NULL, NULL, &mWidth, &mHeight);

	mRenderRect.w = mWidth;
	mRenderRect.h = mHeight;
}


Texture::~Texture() {

	mTex = NULL;
	mGraphics = NULL;
}



Vector2 Texture::ScaledDimensions() {

	Vector2 scaledDimensions = Scale();
	scaledDimensions.x *= mWidth;
	scaledDimensions.y *= mHeight;

	return scaledDimensions;

}

void Texture::Render() {

	Vector2 pos = Position(world);
	Vector2 scale = Scale(world);

	mRenderRect.x = static_cast<int>(pos.x - mWidth *scale.x* 0.5f);
	mRenderRect.y= static_cast<int>(pos.y - mHeight *scale.y* 0.5f);

	mRenderRect.w = static_cast<int>(mWidth * scale.x);
	mRenderRect.h = static_cast<int>(mHeight * scale.y);

	mGraphics->DrawTexture(mTex, &mRenderRect, Rotation(world));
}
