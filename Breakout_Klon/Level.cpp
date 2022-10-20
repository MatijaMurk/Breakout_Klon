#include "Level.h"
#include <iostream>



Level::Level(int level, InfoBar* infoBar, Player* player, Ball* ball, std::string levelPath) {

	mAudio = AudioManager::Instance();
	mTimer = TimerModule::Instance();
	mInfoBar = infoBar;
	mInfoBar->SetLevel(level);
	mLevel = level;
	mLevelStarted = false;
	
	mPlayer = player;
	mBall = ball;

	mContact = player->checkCollision(*ball);
	//>>>>>>READYPLAYER>>>>>>>>>>>>>>>>>>>>>
	mTextTimer = 0.0f;

	mLevelText = new Texture("Level", "Prototype.ttf", 32, { 50,50,200 });
	mLevelText->Parent(this);
	mLevelText->Position(Vector2(Graphics::Instance()->ScreenWidth * .48f, Graphics::Instance()->ScreenHeight * .5f));

	mLevelNumber = new Score();
	mLevelNumber->SetScore(mLevel);
	mLevelNumber->Parent(mLevelText);
	mLevelNumber->Position(Vector2(75.0f,0.0f));

	mLevelOnScreen = 0.0f;
	mLevelOffScreen = 1.5f;

	mReadyText = new Texture("Ready", "Prototype.ttf", 32, { 50,50,200 });
	mReadyText->Parent(this);
	mReadyText->Position(Vector2(Graphics::Instance()->ScreenWidth * .5f, Graphics::Instance()->ScreenHeight * .5f));


	mReadyOnScreen = mLevelOffScreen;
	mReadyOffScreen = mReadyOnScreen + 1.5f;
	//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

	playerDamaged = false;
	mBallRespawnDelay = 2.5f;
	mBallRespawnTimer = 0.0f;
	mBallRespawnOnScreen = 1.0f;

	//>>>>>>GAMEOVER>>>>>>>>>>>>>>>>>>>>>

	mGameOverText = new Texture("GAME OVER", "Prototype.ttf", 46, { 225,50,50 });
	mGameOverText->Parent(this);
	mGameOverText->Position(Vector2(Graphics::Instance()->ScreenWidth * .5f, Graphics::Instance()->ScreenHeight * .5f));
	gameOver = false;
	mGameOverDelay = 3.0f;
	mGameOverTimer = 0.0f;
	mGameOverOnScreen = 1.0f;

	//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

	//>>>>>>GAMEWIN>>>>>>>>>>>>>>>>>>>>>

	mGameWinText = new Texture("YOU WON!", "Prototype.ttf", 54, { 50,225,50 });
	
	mGameWinText->Parent(this);
	mGameWinText->Position(Vector2(Graphics::Instance()->ScreenWidth * .5f, Graphics::Instance()->ScreenHeight * .5f));
	mEscapeText = new Texture("Press BACKSPACE to go back to Main Menu...", "Prototype.ttf", 36, { 150,125,50 });
	mEscapeText->Parent(mGameWinText);
	mEscapeText->Position(Vector2(0.0f,100.0f));
	gameWon= false;
	mGameWinDelay = 1.5f;
	mGameWinTimer = 0.0f;
	mGameWinOnScreen = 1.0f;

	//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

	mBallResetTimer = 0.0f;
	mBallResetDelay = 8.0f;

	mCurrentState = playing;
	mBallResetPos = Vector2(Graphics::Instance()->ScreenWidth * .5f, Graphics::Instance()->ScreenHeight * .86f);

	LoadLevel(levelPath);
}
Level::~Level(){

	mTimer = NULL;
	mInfoBar = NULL;
	mAudio = NULL;
	delete mLevelText;
	mLevelText = NULL;

	delete mLevelNumber;
	mLevelNumber = NULL;

	delete mReadyText;
	mReadyText = NULL;

	delete mBgTexture;
	mBgTexture = NULL;

	delete mGameOverText;
	mGameOverText = NULL;

	delete mGameWinText;
	mGameWinText = NULL;

	delete mEscapeText;
	mGameWinText = NULL;

	mPlayer = NULL;
	mBall = NULL;

	ClearLevel();

}


void Level::LoadLevel(std::string levelPath) {

	if(mCurrentState!=playing)mCurrentState = playing;
	tinyxml2::XMLDocument doc;
	doc.LoadFile(levelPath.c_str());

	if (doc.ErrorID()) {
		std::cerr << "Failed loading the path file: " << levelPath << " !" << std::endl;
		return;
	}

	tinyxml2::XMLElement* level = doc.FirstChildElement("Level");

	SetLevelAttributes(level);
	CreateBrickTypes(level);
	CreateBricks(level);

}
void Level::ClearLevel()
{
	for (auto& itr : mBricks) {
		delete itr;
	}
	mBricks.clear();
	for (auto& itr : mBrickTypes) {
		delete itr.second;
	}
	mBrickTypes.clear();
}
void Level::SetLevelAttributes(tinyxml2::XMLElement* level)
{
	const char* backgroundTexture = "";
	const char* nextLevel = "";

	level->QueryIntAttribute("RowCount", &rowCount);
	level->QueryIntAttribute("ColumnCount", &columnCount);
	level->QueryIntAttribute("RowSpacing", &rowSpacing);
	level->QueryIntAttribute("ColumnSpacing", &columnSpacing);
	level->QueryStringAttribute("BackgroundTexture", &backgroundTexture);
	level->QueryIntAttribute("BrickWidth", &brickWidth);
	level->QueryIntAttribute("BrickHeight", &brickHeight);
	level->QueryStringAttribute("NextLevel", &nextLevel);

	mBgTexture = new Texture(backgroundTexture);
	mBgTexture->Parent(this);
	mBgTexture->Position(Vector2(Graphics::Instance()->ScreenWidth * .5f, Graphics::Instance()->ScreenHeight * .5f));
	this->nextLevel = { nextLevel };
	mLevelPath = nextLevel;
}

void Level::CreateBrickTypes(tinyxml2::XMLElement* level)
{
	tinyxml2::XMLElement* xmlBrickTypes = level->FirstChildElement("BrickTypes");
	for (auto* xmlBrickType = xmlBrickTypes->FirstChildElement("BrickType"); xmlBrickType; xmlBrickType = xmlBrickType->NextSiblingElement("BrickType")) {
		const char* ID = "";
		int hitPoints = 0;
		int breakScore = 0;
		const char* texture = "";
		const char* hitSound = "";
		const char* breakSound = "";

		xmlBrickType->QueryStringAttribute("Id", &ID);
		xmlBrickType->QueryIntAttribute("HitPoints", &hitPoints);
		xmlBrickType->QueryIntAttribute("BreakScore", &breakScore);
		xmlBrickType->QueryStringAttribute("Texture", &texture);
		xmlBrickType->QueryStringAttribute("HitSound", &hitSound);
		xmlBrickType->QueryStringAttribute("BreakSound", &breakSound);

		BrickType* brickType = new BrickType(ID[0], hitPoints, breakScore, texture, hitSound, breakSound);
		mBrickTypes.emplace(ID[0], brickType);
	}
}
void Level::CreateBricks(tinyxml2::XMLElement* level)
{
	tinyxml2::XMLElement* xmlBricks = level->FirstChildElement("Bricks");
	const char* brickText = xmlBricks->GetText();
	if (brickText == nullptr) {
		std::cerr << "Brick layout could not be read!" << std::endl;
		return;
	}

	std::string brickLayout = { brickText };
	brickLayout.erase(std::remove_if(brickLayout.begin(), brickLayout.end(), ::isspace), brickLayout.end());

	float margin = (Graphics::ScreenWidth * 1.065f - ((brickWidth + rowSpacing) * columnCount - rowSpacing)) / 2.2f;
	auto brickCount = brickLayout.begin();

	for (float i = 0; i < rowCount; i++) {
		for (float y = 0; y < columnCount; y++) {
			if (brickCount == brickLayout.end()) {
				std::cerr << "There are more bricks in the layout than defined in the level attributes!" << std::endl;
				return;
		}
			if (*brickCount == '_') {
				++brickCount;
				continue;
			}
			auto brickTypeItr = this->mBrickTypes.find(*brickCount);
			if (brickTypeItr == this->mBrickTypes.end()) {
				std::cerr << "Undefined brick type found in bricks!" << std::endl;
				return;
			}

			Vector2 position = { margin + y * brickWidth + y * columnSpacing, 125.f + i * brickHeight + i * rowSpacing };
			Brick* brick = new Brick(brickTypeItr->second, position);

			mBricks.push_back(brick);
			++brickCount;
		}
	}
}

void Level::BrickCollision(Ball& ball)
{
	if (mContact = mPlayer->checkCollision(ball), mContact.type != CollisionType::None)
	{
		
		ball.CollideWithPaddle(mContact);
		mAudio->PlaySFX("playerHit.wav",0,1);
	}
	
	else if (mContact = ball.CheckWallCollision(),mContact.type != CollisionType::None ) {

		ball.CollideWithWall(mContact);
		if (mContact.type == CollisionType::Bottom) {
			
			HandlePlayerDamaged();
			mBallResetTimer = 0.0f;
			
		}
		if (mContact.type == CollisionType::Right || mContact.type == CollisionType::Left || mContact.type == CollisionType::Top) {
			mAudio->PlaySFX("hitWall.wav", 0, 0);

		}
	}

	for (auto& brick : mBricks) {
		
		if (brick->CollisionWithBall(ball)) {
			mBallResetTimer = 0.0f;
			brick->GetHit();
			
		}	
	}	
	evaluateBricks();
}



bool Level::isFinished()
{
	if (mBricks.size() == 0) {	
		return true;
	}

	for (auto& brick : mBricks) {
		if (!brick->isImpenetrable()) return false;
	}
	
	return true;
}




void Level::StartLevel() {
	
	mLevelStarted = true;
	
}

void Level::HandleStartText() {

	mTextTimer += mTimer->DeltaTime();
	if (mTextTimer >= mLevelOffScreen) {
		if (mLevel > 1) {
			StartLevel();
			mBall->Active(true);
		}
		else {
			if (mTextTimer >= mReadyOffScreen) {
				StartLevel();
				mBall->Active(true);
				mPlayer->Active(true);

			}
		}
	}
}


void Level::evaluateBricks()
{
	mBricks.erase(std::remove_if(mBricks.begin(), mBricks.end(),
		[this](const Brick* brick) -> bool {
			if (brick->isDestroyed()) {
				mPlayer->AddScore((brick->getBreakScore()));
				
				return true;
			}
			return false;
		}
	),
		mBricks.end()
			);
}



void Level::HandleBrickCollision() {

	BrickCollision(*mBall);
	for (auto& brick : mBricks) {
		brick->Update();
	}
}

void Level::HandlePlayerDamaged() {

	if (!playerDamaged) {
		mPlayer->Damaged();
		mInfoBar->SetLives(mPlayer->Lives());
		playerDamaged = true;
		mBallRespawnTimer = 0.0f;
		
	}
}

void Level::HandleGameWin() {

			mPlayer->Active(false);
			mBall->Active(false);
}

void Level::HandleBallOutOfBounds() {
	if (mContact.type == CollisionType::Right || mContact.type == CollisionType::Left || mContact.type == CollisionType::Top) {
		mBallResetTimer += mTimer->DeltaTime();
		if (mBallResetTimer > mBallRespawnDelay) {
			mBall->Position(mBallResetPos);
			BallReset();
		}
	}
}

void Level::BallReset() {

	mBallResetTimer = 0.0f;
	mBall->Active(true);
	mBall->mVelocity = Vector2(static_cast<float>(rand() % 1000) - 250.0f, -mBall->mSpeed);
}

void Level::HandleGameOver() {


	if (mPlayer->Lives() > 0) {

		if (mBallRespawnTimer == 0.0f) 
			mBall->Active(false);
		mBallRespawnTimer += mTimer->DeltaTime();
		if (mBallRespawnTimer >= mBallRespawnDelay) {
			BallReset();
			playerDamaged = false;
		}

	}
	else {

		mGameOverTimer += mTimer->DeltaTime();
		if (mGameOverTimer >= mGameOverDelay) {
			mBall->Active(false);
			mCurrentState = gameover;
		}
		
	}
}

Level::LevelStates Level::State() {
	return mCurrentState;
}

void Level::Update() {

	if (!mLevelStarted) {
		HandleStartText();
	}
	else {
		HandleBrickCollision();
		HandleBallOutOfBounds();
		if (playerDamaged) {
			HandleGameOver();
		}
		
		if (InputManager::Instance()->KeyDown(SDL_SCANCODE_N)) {
			ClearLevel();
			mCurrentState = finished;
			if (mLevelPath.empty())
				gameWon = true;
		}
		if (isFinished()) {
			ClearLevel();
			mCurrentState=finished;
			if (mLevelPath.empty())
				gameWon = true;
			
		}
		if (gameWon) {
			HandleGameWin();
			
		}
		
	}
}
void Level::Render() {

	mBgTexture->Render();
	for (auto& brick : mBricks) {
		brick->Render();
	}


	if (!mLevelStarted) {
		if (mTextTimer > mLevelOnScreen && mTextTimer < mLevelOffScreen) {
			mLevelText->Render();
			mLevelNumber->Render();

		}
		else if (mTextTimer > mReadyOnScreen && mTextTimer < mReadyOffScreen) {
			mReadyText->Render();
		}
	}

	else {
		if (playerDamaged) {
			if (mBallRespawnTimer >= mBallRespawnOnScreen) {
				mReadyText->Render();
				mBall->Position(mBallResetPos);
			}

			else if(mGameOverTimer >= mGameOverOnScreen)
				mGameOverText->Render();
		}
		if (gameWon) {
			mGameWinText->Render();
			mEscapeText->Render();
			
		}
			
	}
	



}
