#pragma once


#include "TimerModule.h"
#include"ScreenManager.h"
#include "AudioManager.h"



class GameManager
{
private:
	static GameManager* instance;
	const int frameRate =60;

	
	Graphics* graphics;
	AssetManager* mAssetManager;
	InputManager* mInputManager;
	AudioManager* mAudioManager;

	TimerModule* timer;
	SDL_Event events;

	ScreenManager* mScreenManager;
	



public:
	bool quit;
	static GameManager* Instance();

	static void Release();

	void Run();

private:

	GameManager();
	~GameManager();

	void EarlyUpdate();
	void Update();
	void LateUpdate();
	void Render();
};

