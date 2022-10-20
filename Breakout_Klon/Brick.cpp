#include "Brick.h"
#include "BoxCollider.h"
Brick::Brick(BrickType* brickType, Vector2 pos) :
	brickType(brickType),
	hitPoints(brickType->hitPoints) {

	mAudio = AudioManager::Instance();
	mTimer = TimerModule::Instance();
	
	brickTexture = new Texture(brickType->mTexture);
	brickTexture->Parent(this);
	brickTexture->Position(pos);
	height = static_cast<int>(brickTexture->ScaledDimensions().y);
	width = static_cast<int>(brickTexture->ScaledDimensions().x);
	
	
}

Brick::~Brick() {

	mAudio = NULL;
	mTimer = NULL;

}

void Brick::Update() {}

bool Brick::isUpperSideOfLine(Point* corner1, Point* corner2, Point* ballCenter) {

	return ((corner2->x - corner1->x) * (ballCenter->y - corner1->y) - (corner2->y - corner1->y) * (ballCenter->x - corner1->x)) > 0;
}

int Brick::getContactEdge(Ball& ball) {
	Point brickA{}, brickB{}, brickC{}, brickD{}, ballCenter{};
	brickA.x = brickTexture->Position().x-width*.5f;
	brickA.y = brickTexture->Position().y;

	//Gornji desni  kut
	brickB.x = brickTexture->Position().x+width*.5f;
	brickB.y = brickTexture->Position().y;

	//Donji desni kut
	brickC.x = brickTexture->Position().x + width*.5f;
	brickC.y = brickTexture->Position().y + height;

	//Donji lijevi kut
	brickD.x = brickTexture->Position().x-width*.5f;
	brickD.y = brickTexture->Position().y + height;

	ballCenter.x = ball.position.x + ball.width*.5f;
	ballCenter.y = ball.position.y + ball.height * .5f;

	
	bool isAboveAC = isUpperSideOfLine(&brickC, &brickA, &ballCenter);
	bool isAboveBD = isUpperSideOfLine(&brickB, &brickD, &ballCenter);

	if (isAboveAC)
	{
		if (isAboveBD)
		{
			ball.FlipDirectionY();

			return 1;
		}
		else
		{	
			ball.FlipDirectionX();
			return 2;
		}
	}
	else
	{
		if (isAboveBD)
		{
			ball.FlipDirectionX();
			return 4;
		}
		else
		{
			ball.FlipDirectionY();
			return 3;
		}
	}

}

bool Brick::CollisionWithBall(Ball& ball) {

	if (!hit) {

		float brickX = brickTexture->Position().x;
		float brickY = brickTexture->Position().y;

		float ballCenterX = ball.position.x + ball.width * .5f;
		float ballCenterY = ball.position.y + ball.height * .5f;

		float brickCenterX = brickX + 0.5f * width;
		float brickCenterY = brickY + 0.5f * height;

		if (brickTexture->Position().x + width*.5f >= ball.position.x
			&& brickTexture->Position().x -width*.5f<= ball.position.x + ball.width
			&& brickTexture->Position().y + height >= ball.position.y
			&& brickTexture->Position().y <= ball.position.y + ball.height)
		{
			getContactEdge(ball);
			hit = true;
			
			return true;
		}

	}
	hit = false;
	return false;
}

void Brick::GetHit() {

	
	if (hitPoints < 0) { 
	mAudio->PlaySFX(brickType->mHitSound, 0, 1);
	return; 
	}
	hitPoints--;
	if (hitPoints == 0) {
		mAudio->PlaySFX(brickType->mBreakSound,0,2);
	}
	else mAudio->PlaySFX(brickType->mHitSound, 0, 1);
}

bool Brick::isDestroyed() const {

	return hitPoints == 0;
}

bool Brick::isImpenetrable() {
	return hitPoints < 0;
}


unsigned Brick::getBreakScore() const {
	return brickType->breakScore;
}

void Brick::Render() {

	brickTexture->Render();
}


