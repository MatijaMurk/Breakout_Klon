#include "Player.h"




Player::Player() {

	mTimer = TimerModule::Instance();
	mInput = InputManager::Instance();
    mAudio = AudioManager::Instance();

	score = 0;
	livesLeft = 5;

	mPlayerTex = new Texture("player.png");
	mPlayerTex->Parent(this);
	mPlayerTex->Position(zeroV2);
	

    width = static_cast<int>( mPlayerTex->ScaledDimensions().x);
    height = static_cast<int>(mPlayerTex->ScaledDimensions().y);

	moveSpeed = 800.0f;
	mMoveBounds = Vector2(Graphics::ScreenWidth * 0.09f, Graphics::ScreenWidth*.91f);
    

}

Player::~Player() {

	mTimer = NULL;
	mInput = NULL;
    mAudio = NULL;

	delete mPlayerTex;
	mPlayerTex = NULL;
}

 void Player::Movement(){


	 if (mInput->KeyDown(SDL_SCANCODE_A) || mInput->KeyDown(SDL_SCANCODE_LEFT)) {
		Move(Vector2(-moveSpeed, 0.0f) * mTimer->DeltaTime(),world);

	 }
	 else if (mInput->KeyDown(SDL_SCANCODE_D) || mInput->KeyDown(SDL_SCANCODE_RIGHT)) {
		Move(Vector2(moveSpeed, 0.0f) * mTimer->DeltaTime(),world);
	 }

	 Vector2 pos = Position(local);
	 if (pos.x < mMoveBounds.x)
		 pos.x = mMoveBounds.x;
	 else if (pos.x > mMoveBounds.y)
		 pos.x = mMoveBounds.y;

	 Position(pos);
 }

int Player::Score() {
	return score;
}

Contact Player::checkCollision(Ball const& ball)
{
    float ballLeft = ball.position.y - ball.width * .5f;
    float ballRight = ball.position.y + ball.width * .5f;
    float ballTop = ball.position.x;
    float ballBottom = ball.position.x + ball.height;

    float paddleLeft = mPlayerTex->Position().y;
    float paddleRight = mPlayerTex->Position().y + height;
    float paddleTop = mPlayerTex->Position().x-width*.5f;
    float paddleBottom = mPlayerTex->Position().x+width*.5f;

 

    Contact contact{};

    if (ballLeft >= paddleRight)
    {
        return contact;
    }

    if (ballRight <= paddleLeft)
    {
        return contact;
    }

    if (ballTop >= paddleBottom)
    {
        return contact;
    }

    if (ballBottom <= paddleTop)
    {
        return contact;
    }

    float paddleRangeUpper = paddleBottom - (2.f * width / 3.0f);
    float paddleRangeMiddle = paddleBottom - (width /3.0f);

    if (ball.mVelocity.y < 0)
    {
        
        contact.penetration = paddleRight - ballLeft;
    }
    else if (ball.mVelocity.y > 0)
    {
       
        contact.penetration = paddleLeft - ballRight;
    }

    if ((ballBottom > paddleTop)
        && (ballBottom < paddleRangeUpper))
    {
        contact.type = CollisionType::Top;
    }
    else if ((ballBottom > paddleRangeUpper)
        && (ballBottom < paddleRangeMiddle))
    {
        contact.type = CollisionType::Middle;
    }
    else
    {
        contact.type = CollisionType::Bottom;
    }

    return contact;
}

int Player::Lives() {
	return livesLeft;
}
void Player::AddScore(int scoreToAdd) {

	score += scoreToAdd;
}


void Player::Damaged() {

    livesLeft--;
    mAudio->PlaySFX("loseLife.wav");
}

void Player::Update(){
	if (Active()) {
		Movement();
	}
}

void Player::Render(){

	mPlayerTex->Render();
	

}