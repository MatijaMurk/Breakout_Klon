#include "GameManager.h"

GameManager* GameManager::instance = NULL;

GameManager* GameManager::Instance() {
	if (instance == NULL) {

		instance = new GameManager();
	}

	return instance;
}

void GameManager::Release() {


	delete instance;
	instance = NULL;

}

GameManager::GameManager() {

	quit = false;
	events = SDL_Event();

	graphics = Graphics::Instance();

	if (!Graphics::Initialized())
		quit = true;

	mAssetManager = AssetManager::Instance();

	mInputManager = InputManager::Instance();

	mAudioManager = AudioManager::Instance();

	timer = TimerModule::Instance();

	mScreenManager = ScreenManager::Instance();
	
}

GameManager::~GameManager() {

	ScreenManager::Release();
	mScreenManager = NULL;

	AssetManager::Release();
	mAssetManager = NULL;
	
	Graphics::Release();
	graphics = NULL;

	AudioManager::Release();
	mAudioManager = NULL;

	InputManager::Release();
	mInputManager = NULL;

	TimerModule::Release();
	timer = NULL;
	

}

void GameManager::EarlyUpdate() {
	timer->Reset();
	mInputManager->Update();
}
void GameManager::Update() {

	mScreenManager->Update();

}

void GameManager::LateUpdate() {
	
}

void GameManager::Render() {

	graphics->ClearBackBuffer();
	mScreenManager->Render();
	graphics->Render();
}

void GameManager::Run() {

	while (!quit) {

		timer->Update();
		while (SDL_PollEvent(&events) != 0) {
			if (events.type == SDL_QUIT) {
				quit = true;
			}

			
		}
		if (timer->DeltaTime() >= 1.0f / frameRate) {

			
			EarlyUpdate();
			Update();
			LateUpdate();
			Render();

			
		}
		
	}

}
