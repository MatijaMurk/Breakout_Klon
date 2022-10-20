#include "InfoBar.h"

InfoBar::InfoBar() {

	mTimer = TimerModule::Instance();
	mAudio = AudioManager::Instance();

	mInfoBar = new GameObject(Vector2(Graphics::Instance()->ScreenWidth * .5f, 90.0f));

	mInfoBarBG = new Texture("InfoBarDivider.png");

	mLivesLeftText = new Texture("Lives", "Prototype.ttf", 32, { 50,150,210 });
	mLivesLeftNum = new Score();

	mScoreText = new Texture("Score", "Prototype.ttf", 32, { 160,210,25 });
	mPlayerScore = new Score();

	mLevelText = new Texture("Level", "Prototype.ttf", 32, { 210,75,25 });
	mLevelNum = new Score();

	mInfoBarBG->Parent(mInfoBar);

	mLivesLeftText->Parent(mInfoBar);
	mLivesLeftNum->Parent(mLivesLeftText);

	mScoreText->Parent(mInfoBar);
	mPlayerScore->Parent(mScoreText);

	mLevelText->Parent(mInfoBar);
	mLevelNum->Parent(mLevelText);

	mInfoBarBG->Position(Vector2(-Graphics::Instance()->ScreenWidth * 0.0f, 0.0f));

	mLivesLeftText->Position(Vector2(-Graphics::Instance()->ScreenWidth * 0.3f, -75.0f));
	mLivesLeftNum->Position(Vector2(25.0f, 50.0f));
	

	mScoreText->Position(Vector2(-Graphics::Instance()->ScreenWidth * 0.0f, -75.0f));
	mPlayerScore->Position(Vector2(100.0f, 50.0f));

	mLevelText->Position(Vector2(-Graphics::Instance()->ScreenWidth * -0.3f, -75.0f));
	mLevelNum->Position(Vector2(25.0f, 50.0f));



}

InfoBar::~InfoBar() {

	mTimer = NULL;
	mAudio = NULL;

	delete mInfoBar;
	mInfoBar = NULL;

	delete mLivesLeftText;
	mLivesLeftText = NULL;

	delete mLivesLeftNum;
	mLivesLeftNum = NULL;

	delete mScoreText;
	mScoreText = NULL;

	delete mPlayerScore;
	mPlayerScore = NULL;

	delete mLevelText;
	mLevelText = NULL;

	delete mLevelNum;
	mLevelNum = NULL;

}

void InfoBar::SetScore(int score) {

	mPlayerScore->SetScore(score);

}

void InfoBar::SetLives(int lives) {

	
	mLivesLeftNum->SetScore(lives);

}

void InfoBar::SetLevel(int level) {

	
	mLevelNum->SetScore(level);
}

void InfoBar::Update(){}

void InfoBar::Render(){

	mInfoBarBG->Render();
	mLivesLeftText->Render();
	mLivesLeftNum->Render();
	mScoreText->Render();
	mPlayerScore->Render();
	mLevelText->Render();
	mLevelNum->Render();

}
