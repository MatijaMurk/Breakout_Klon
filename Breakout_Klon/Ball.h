#pragma once
#include "GameObject.h"
#include "TimerModule.h"
#include "Texture.h"
#include "Contact.h"


class Ball : public GameObject
{
private:

	TimerModule* mTimer;

	Texture* mBall;

public:

	Ball();
	~Ball();

	void Reset();
	void Movement();
	
	void CollideWithPaddle(Contact const& contact);
	void CollideWithWall(Contact const& contact);
	Contact CheckWallCollision();

	void FlipDirectionX();
	void FlipDirectionY();

	Vector2 position;
	Vector2 mVelocity;

	float mSpeed;

	int height;
	int width;

	void Update();
	void Render();

};

