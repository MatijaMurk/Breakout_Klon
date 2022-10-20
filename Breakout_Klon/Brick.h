#pragma once
#include "GameObject.h"
#include "Texture.h"
#include "AudioManager.h"
#include "Ball.h"
#include "TimerModule.h"

struct BrickType {
	BrickType(char ID, int hitPoints, int breakScore, std::string texture, std::string hitsound, std::string breaksound) :
		ID(ID),
		hitPoints(hitPoints),
		breakScore(breakScore)
	{
		if (!texture.empty()) {
			this->mTexture = texture;
		}
		if (!texture.empty()) {
			
			this->mHitSound = hitsound;
		}
		if (!texture.empty()) {
			
			this->mBreakSound = breaksound;
		}
	}

	const char ID;
	const int hitPoints;
	const int breakScore;

	std::string mTexture;
	std::string mHitSound;
	std::string mBreakSound;
};

struct Point {
	float x, y;
};

class Brick : public GameObject
{

private:

	TimerModule* mTimer;
	AudioManager* mAudio;
	BrickType* brickType;
	Texture* brickTexture;
	int hitPoints;
	int height;
	int width;


public:

	Brick(BrickType* brickType, Vector2 position);
	~Brick();

	bool hit = false;

	void GetHit();
	bool isDestroyed() const;
	bool isImpenetrable();
	unsigned getBreakScore() const;
	void Render();
	void Update();
	bool CollisionWithBall(Ball& ball);
	int getContactEdge(Ball& ball);
	bool isUpperSideOfLine(Point*, Point*, Point*);

	
	
};

