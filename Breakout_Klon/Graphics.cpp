#include "Graphics.h"

Graphics* Graphics::instance = NULL;
bool Graphics::initialized = false;

Graphics* Graphics::Instance() {

	if (instance == NULL) {
		instance = new Graphics();
	}
	return instance;
}

void Graphics::Release() {
	delete instance;
	instance = NULL;
	initialized = false;
}

bool Graphics::Initialized() {
	return initialized;
}

Graphics::Graphics() {
	backBuffer = NULL;
	
	initialized = Init();
}

Graphics::~Graphics() {

	SDL_DestroyWindow(window);
	window = NULL;

	SDL_DestroyRenderer(mRenderer);
	mRenderer = NULL;

	TTF_Quit();
	IMG_Quit();
	SDL_Quit();
}

bool Graphics::Init() {

	if (SDL_Init(SDL_INIT_VIDEO|SDL_INIT_AUDIO) < 0) {
		printf("SDL init error: %s\n", SDL_GetError());
		return false;
	}

	window = SDL_CreateWindow(WindowName, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, ScreenWidth, ScreenHeight, SDL_WINDOW_SHOWN);

	if (window == NULL) {
		printf("Window creation error: %s\n", SDL_GetError());
		return false;
	}

	mRenderer = SDL_CreateRenderer(window,-1,SDL_RENDERER_ACCELERATED);

	if (mRenderer == NULL) {
		printf("Renderer creation error: %s\n", SDL_GetError());
		return false;
	}

	SDL_SetRenderDrawColor(mRenderer, 0x00, 0x00, 0x00, 0x00);

	int flags = IMG_INIT_PNG;
	if (!(IMG_Init(flags) & flags)) {
		printf("Image init error: %s\n", IMG_GetError());
		return false;
	}

	if (TTF_Init() == -1) {
		printf("Font init Error: %s\n", TTF_GetError());
		return false;
	}

	backBuffer = SDL_GetWindowSurface(window);

	return true;

}

SDL_Texture* Graphics::LoadTexture(std::string path) {

	SDL_Texture* tex = NULL;
	SDL_Surface* surface = IMG_Load(path.c_str());

	if (surface == NULL) {
		printf("Error loading texture: Path(%s), Error(%s)\n", path.c_str(), IMG_GetError());
		return tex;
	}

	tex = SDL_CreateTextureFromSurface(mRenderer, surface);
	if (tex == NULL) {
		printf("Texture creation Error: %s\n", SDL_GetError());
		return tex;
	}

	SDL_FreeSurface(surface);

	return tex;


}

SDL_Texture* Graphics::CreateTextTexture(TTF_Font* font, std::string text, SDL_Color color) {

	
		SDL_Surface* surface = TTF_RenderUTF8_Solid(font, text.c_str(), color);
		if (surface == NULL) {
			printf("Text Render Error:%s\n", TTF_GetError());
			return NULL;
		}

		SDL_Texture* tex = SDL_CreateTextureFromSurface(mRenderer, surface);

		if (tex == NULL) {
			printf("text Texture creation Error: %s\n", SDL_GetError());
			return NULL;
		}
		SDL_FreeSurface(surface);
		return tex;
	
}

void Graphics::ClearBackBuffer() {

	SDL_RenderClear(mRenderer);
}

void Graphics::DrawTexture(SDL_Texture* tex, SDL_Rect* rend, float angle, SDL_RendererFlip flip) {

	SDL_RenderCopyEx(mRenderer, tex, NULL, rend, angle, NULL, flip );
}

void Graphics::Render() {

	SDL_RenderPresent(mRenderer);
}