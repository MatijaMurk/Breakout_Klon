#include "PlayScreen.h"


PlayScreen::PlayScreen() {

	mTimer = TimerModule::Instance();

	mInput = InputManager::Instance();

	mAudio = AudioManager::Instance();

	mInfoBar = new InfoBar();
	mStartText = new Texture("Press SPACE to start!", "Prototype.ttf", 32, { 250,250,250 });
	mStartText->Parent(this);
	mStartText->Position(Vector2(Graphics::Instance()->ScreenWidth * .5f,Graphics::Instance()->ScreenHeight*.5f));
	
	mLevel = NULL;
	mCurrentLevel = NULL;
	mLevelStarted = false;
	mGameStarted = false;
	mPlayer = NULL;
	mBall = NULL;
	mLevelPath = "Assets/Levels/Level1.xml";

}

PlayScreen::~PlayScreen() {

	mTimer = NULL;
	mInput = NULL;
	
	mAudio = NULL;



	delete mInfoBar;
	mInfoBar = NULL;

	delete mStartText;
	mStartText = NULL;

	delete mLevel;
	mLevel = NULL;

	delete mPlayer;
	mPlayer = NULL;

	delete mBall;
	mBall = NULL;
}


void PlayScreen::StartNextLevel() {

	
	delete mBall;
	mBall = new Ball();
	mBall->Parent(this);
	mBall->Position(Vector2(Graphics::Instance()->ScreenWidth * .5f, Graphics::Instance()->ScreenHeight * .86f));
	mBall->Active(false);
	mLevelStarted = true;
	mCurrentLevel++;
	
	delete mLevel;
	mLevel = new Level(mCurrentLevel, mInfoBar, mPlayer, mBall, mLevelPath);

	mLevelPath = mLevel->mLevelPath;
	
}

void PlayScreen::StartNewGame() {

	
	delete mPlayer;
	mPlayer = new Player();
	mPlayer->Parent(this);
	mPlayer->Position(Vector2(Graphics::Instance()->ScreenWidth * .5f, Graphics::Instance()->ScreenHeight * .9f));
	mPlayer->Active(false);
	
	
	mInfoBar->SetScore(mPlayer->Score());
	mInfoBar->SetLives(mPlayer->Lives());
	mGameStarted = false;
	mAudio->PlayMusic("gameMusic.wav");
	mCurrentLevel = 0;
	mLevelStarted = false;
	mInfoBar->SetLevel(mCurrentLevel);
	

}

bool PlayScreen::GameOver() {

	if (!mLevelStarted)return false;

	return(mLevel->State() == Level::gameover);
}


void PlayScreen::Update() {

	if (!mGameStarted) {
		if (mInput->KeyDown(SDL_SCANCODE_SPACE)) {
			mGameStarted = true;
			StartNextLevel();
		}
	}
	
	if (mGameStarted && mLevelStarted) {
		mInfoBar->Update();
		mLevel->Update();
		mPlayer->Update(); 
		mBall->Update();
		if (mLevel->State()==Level::finished) {
			
			if (!mLevelPath.empty()) {
				mLevelStarted = false;
				StartNextLevel();
			}		
		}
	}
	mInfoBar->SetScore(mPlayer->Score());
	
	
}

void PlayScreen::Render() {

	
	
	if (!mGameStarted) {
		mStartText->Render();
	}

	if (mGameStarted && mLevelStarted) {
		mLevel->Render();
		mPlayer->Render();
		mBall->Render();
		mInfoBar->Render();
	}
	
}