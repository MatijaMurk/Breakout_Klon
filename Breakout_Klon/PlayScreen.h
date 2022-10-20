#pragma once

#include "Level.h"
#include "Ball.h"


class PlayScreen : public GameObject
{
private:
	TimerModule* mTimer;
	InputManager* mInput;
	AudioManager* mAudio;


	Level* mLevel;
	bool mLevelStarted;
	int mCurrentLevel;
	bool mGameStarted;
	
	Texture* mStartText;

	InfoBar* mInfoBar;

	Player* mPlayer;
	
	Ball* mBall;

private:
	
	void StartNextLevel();

public:
	std::string mLevelPath;
	PlayScreen();
	~PlayScreen();

	bool GameOver();

	void StartNewGame();

	void Update();
	void Render();

};

