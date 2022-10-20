#pragma once
#include "GameObject.h"
#include "InputManager.h"
#include "TimerModule.h"
#include "Contact.h"
#include "Ball.h"
#include "AudioManager.h"


class Player : public GameObject
{
private:
	TimerModule* mTimer;
	InputManager* mInput;
	AudioManager* mAudio;

	Texture* mPlayerTex;
	int score;
	int livesLeft;

	int width;
	int height;

	float moveSpeed;
	Vector2 mMoveBounds;
	

private:
	void Movement();

public:
	Player();
	~Player();

	
	Contact checkCollision(Ball const& ball);
	int Score();
	int Lives();
	void AddScore(int scoreToAdd);
	void Damaged();
	void Update();
	void Render();
};

