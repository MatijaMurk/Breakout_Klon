#pragma once

#include "TimerModule.h"
#include "Score.h"
#include "AudioManager.h"

class InfoBar : public GameObject
{
private:

	TimerModule* mTimer;
	AudioManager* mAudio;

	GameObject* mInfoBar;

	Texture* mLivesLeftText;
	Score* mLivesLeftNum;
	

	Texture* mLevelText;
	Score* mLevelNum;
	

	Texture* mScoreText;
	Score* mPlayerScore;

	Texture* mInfoBarBG;

public:

	InfoBar();
	~InfoBar();

	void SetScore(int score);
	void SetLives(int lives);
	void SetLevel(int level);

	void Update();
	void Render();
	
};

