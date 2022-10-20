#pragma once

#include "Math.h"
class GameObject
{

public:

	enum SPACE { local = 0, world = 1 };

private:

	Vector2 mPos;
	float mRotation;
	Vector2 mScale;

	bool mActive;
	GameObject* mParent;

public:

	GameObject(Vector2 pos = zeroV2);
	~GameObject();

	void Position(Vector2 pos);
	Vector2 Position(SPACE space = world);


	void Rotation(float rotation);
	float Rotation(SPACE space = world);

	void Scale(Vector2 scale);
	Vector2 Scale(SPACE space = world);

	void Active(bool active);
	bool Active();

	void Parent(GameObject* parent);
	GameObject* Parent();

	void Move(Vector2 vec, SPACE space=local);
	void Rotate(float amount);

	virtual void Update();
	virtual void Render();

};

