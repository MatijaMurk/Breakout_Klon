#include "Ball.h"


Ball::Ball()
{
	mTimer = TimerModule::Instance();

	mBall = new Texture("ball.png");
	mBall->Parent(this);
	mBall->Position(zeroV2);

	mSpeed = 700.0f;
	mVelocity = Vector2(static_cast<float>(rand() % 1000 - 250), -mSpeed);

	height = static_cast<int>(mBall->ScaledDimensions().y);
	width = static_cast<int>(mBall->ScaledDimensions().x);
}

Ball::~Ball()
{
	mTimer = nullptr;
	delete mBall;
	mBall = nullptr;
}


void Ball::Movement()
{
	Move(mBall->Position(local) += mVelocity * mTimer->DeltaTime());
}


Contact Ball::CheckWallCollision()
{
	float ballLeft = mBall->Position(world).x - width * .5f;
	float ballRight = mBall->Position(world).x + width * .5f;
	float ballTop = mBall->Position(world).y;
	float ballBottom = mBall->Position(world).y + height;

	Contact contact{};

	if (ballLeft < 0.0f)
	{
		contact.type = CollisionType::Left;
		contact.penetration = -ballLeft;
	}
	else if (ballRight > Graphics::ScreenWidth)
	{
		contact.type = CollisionType::Right;
		contact.penetration = Graphics::ScreenWidth - ballRight;
	}
	else if (ballTop < 105.f)
	{
		contact.type = CollisionType::Top;
		contact.penetration = -ballTop;
	}
	else if (ballBottom > Graphics::ScreenHeight * 1.1f)
	{
		contact.type = CollisionType::Bottom;
		contact.penetration = Graphics::ScreenHeight - ballBottom;
	}

	return contact;
}

void Ball::CollideWithPaddle(const Contact& contact)
{
	position.y += contact.penetration;
	mVelocity.y = -mVelocity.y;

	if (contact.type == CollisionType::Top)
	{
		mVelocity.x = -0.75f * mSpeed;
	}
	else if (contact.type == CollisionType::Bottom)
	{
		mVelocity.x = 0.75f * mSpeed;
	}
}

void Ball::CollideWithWall(const Contact& contact)
{
	if ((contact.type == CollisionType::Top))
	{
		position.y += contact.penetration;
		mVelocity.y = -mVelocity.y;
	}
	else if ((contact.type == CollisionType::Left)
		|| (contact.type == CollisionType::Right))
	{
		position.x += contact.penetration;
		mVelocity.x = -mVelocity.x;
	}
}

void Ball::FlipDirectionX()
{
	mVelocity.x = -mVelocity.x;
}

void Ball::FlipDirectionY()
{
	mVelocity.y = -mVelocity.y;
}

void Ball::Reset()
{
	Active(false);

	mBall->Position(zeroV2);
	mVelocity = Vector2(static_cast<float>(rand() % 1000 - 250), -mSpeed);
	Active(true);
}

void Ball::Update()
{
	if (Active())
	{
		Movement();
		position = mBall->Position(world);
	}
}

void Ball::Render()
{
	mBall->Render();
}
