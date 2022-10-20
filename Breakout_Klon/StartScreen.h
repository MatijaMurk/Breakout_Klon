#pragma once

#include "Texture.h"
#include "InputManager.h"
#include "AudioManager.h"



class StartScreen : public GameObject
{

private:

	AudioManager* mAudio;
	GameObject* mMenu;

	Texture* mTitle;
	
	Texture* mPressEnter;
	Texture* mPressExit;

public:

	StartScreen();
	~StartScreen();
	bool doOnce;
	void PlayMusic();
	void Update();
	void Render();

	
};

