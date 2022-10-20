#include "StartScreen.h"

StartScreen::StartScreen(){

	
	mAudio = AudioManager::Instance();
	mMenu = new GameObject(Vector2(Graphics::Instance()->ScreenWidth * .5f, 80.0f));
	

	mTitle = new Texture("brejkautlogo.png");
	
	mPressEnter = new Texture("Press Enter to play", "Prototype.ttf", 56, { 160,210,25 });
	mPressExit= new Texture("Press ESC to quit", "Prototype.ttf",46, { 210,75,25 });

	mTitle->Parent(mMenu);
	
	mPressEnter->Parent(mMenu);
	mPressExit->Parent(mMenu);

	mTitle->Position(Vector2(-Graphics::Instance()->ScreenWidth*0.0f,200.0f));
	
	mPressEnter->Position(Vector2(-Graphics::Instance()->ScreenWidth * 0.0f, 400.0f));
	mPressExit->Position(Vector2(-Graphics::Instance()->ScreenWidth * 0.0f, 500.0f));

	mMenu->Parent(this);
	
	doOnce = true;

}
StartScreen::~StartScreen(){


	mAudio = NULL;
	delete mMenu;
	mMenu = NULL;

	delete mTitle;
	mTitle = NULL;

	delete mPressEnter;
	mPressEnter = NULL;

	delete mPressExit;
	mPressExit = NULL;

}

void StartScreen::PlayMusic() {

	mAudio->PlayMusic("bgMusic.wav");
}

void StartScreen::Update(){
	if (doOnce) {
		PlayMusic();
		doOnce = false;
	}
}
void StartScreen::Render() {

	mTitle->Render();
	
	mPressEnter->Render();
	mPressExit->Render();

}
