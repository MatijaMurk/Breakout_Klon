#include "ScreenManager.h"

ScreenManager* ScreenManager::sInstance = NULL;

ScreenManager* ScreenManager::Instance() {

	if (sInstance == NULL) {
		sInstance = new ScreenManager();
	}
	

	return sInstance;
}

void ScreenManager::Release() {

	delete sInstance;
	sInstance = NULL;

}

ScreenManager::ScreenManager(){

	mInput = InputManager::Instance();

	mAudio = AudioManager::Instance();

	mStartScreen = new StartScreen();
	mPlayScreen = new PlayScreen();

	mCurrentScreen = start;

}

ScreenManager::~ScreenManager(){

	mInput = NULL;
	mAudio = NULL;
	
	delete mStartScreen;
	mStartScreen=NULL;

	delete mPlayScreen;
	mPlayScreen = NULL;
}


void ScreenManager::Update() {

	switch (mCurrentScreen) {
	case start:
		mStartScreen->Update();
		if (mInput->KeyDown(SDL_SCANCODE_RETURN)) {
			
			mPlayScreen->mLevelPath = "Assets/Levels/Level1.xml";
			mCurrentScreen = play;
			mPlayScreen->StartNewGame();
			
		}
		if (mInput->KeyDown(SDL_SCANCODE_ESCAPE)) {
			SDL_Quit();
		}
		
		break;

	case play:
		mPlayScreen->Update();	
		if (mPlayScreen->GameOver()||mInput->KeyDown(SDL_SCANCODE_BACKSPACE)) {
			mStartScreen->doOnce = true;
			mCurrentScreen = start;
		}	
		break;
	}
}

void ScreenManager::Render() {

	switch (mCurrentScreen) {
	case start:
		mStartScreen->Render();	
		break;

	case play:
		mPlayScreen->Render();
		break;
	}
}