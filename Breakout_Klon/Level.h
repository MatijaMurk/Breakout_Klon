#pragma once

#include "InfoBar.h"
#include "Player.h"
#include "Ball.h"
#include "tinyxml2.h"
#include "Brick.h"
#include <unordered_map>
#include "Contact.h"
//#include "AudioManager.h"

using BrickTypes = std::unordered_map<char, BrickType*>;

class Level :public GameObject
{

public :
	enum LevelStates{gameover, finished, playing};

private:
	AudioManager* mAudio;
	TimerModule* mTimer;
	InfoBar* mInfoBar;

	int mLevel;
	bool mLevelStarted;


	float mTextTimer;

	Texture* mLevelText;
	Score* mLevelNumber; 
	float mLevelOnScreen;
	float mLevelOffScreen;

	Contact mContact;
	

	Texture* mReadyText;
	float mReadyOnScreen;
	float mReadyOffScreen;

	bool playerDamaged;

	Texture* mGameWinText;
	Texture* mEscapeText;
	float gameWon;
	float mGameWinDelay;
	float mGameWinTimer;
	float mGameWinOnScreen;

	Texture* mGameOverText;
	bool gameOver;
	float mGameOverDelay;
	float mGameOverTimer;
	float mGameOverOnScreen;

	float mBallRespawnDelay;
	float mBallRespawnTimer;
	float mBallRespawnOnScreen;

	float mBallResetDelay;
	float mBallResetTimer;

	LevelStates mCurrentState;

	Texture* mBgTexture;
	Player* mPlayer;
	Ball* mBall;

	Vector2 mBallResetPos;

private:
	void StartLevel();
	void HandleStartText();
	void LoadLevel(std::string levelPath);
	void ClearLevel();
	void SetLevelAttributes(tinyxml2::XMLElement* level);
	void CreateBrickTypes(tinyxml2::XMLElement* level);
	void CreateBricks(tinyxml2::XMLElement* level);
	
	void HandleBallOutOfBounds();
	void BallReset();
	void HandleGameWin();

	void HandleBrickCollision();
	void HandlePlayerDamaged();
	void HandleGameOver();

	void evaluateBricks();

	std::vector<Brick*> mBricks;
	BrickTypes mBrickTypes;

	int rowCount;
	int columnCount;
	int rowSpacing;
	int columnSpacing;
	int brickWidth;
	int brickHeight;
	std::string nextLevel;
	

public:


	Level(int level, InfoBar* infoBar, Player* player, Ball* mBall, std::string levelPath);
	~Level();
	std::string mLevelPath;


	LevelStates State();

	
	bool isFinished();
	void BrickCollision(Ball& ball);

	void Update();
	void Render();

};

