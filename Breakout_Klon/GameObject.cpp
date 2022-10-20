#include "GameObject.h"
#include <SDL.h>


GameObject::GameObject(Vector2 pos) {
	
	mPos = pos;
	mRotation = 0.0f;
	mActive = true;
	mParent = NULL;
	mScale = oneV2;
}

GameObject::~GameObject() {
	mParent = NULL;
}



void GameObject::Position(Vector2 pos) {
	mPos = pos;
}
Vector2 GameObject::Position(SPACE space) {
	if (space == local || mParent == NULL) {
		return mPos;
	}
	Vector2 parentScale = mParent->Scale(world);
	Vector2 rotatePos = RotateVector(Vector2(mPos.x * parentScale.x, mPos.y * parentScale.y), mParent->Rotation(local));
	return mParent->Position(world)+rotatePos;
}
void GameObject::Rotation(float r) {

	mRotation = r;
	if (mRotation > 360.0f) {
		float mul = mRotation / 360;
		mRotation -= 360.0f * mul;
	}
	else if (mRotation < 0.0f) {
		float mul = (mRotation / 360) - 1;
		mRotation -= 360.0f * mul;
	}
}

float GameObject::Rotation(SPACE space) {

	if ( space==local||mParent == NULL) 
		return mRotation;
	

	return mParent->Rotation(world) + mRotation;
}

void GameObject::Scale(Vector2 scale) {

	mScale = scale;
}

Vector2 GameObject::Scale(SPACE space) {
	if (space == local || mParent == NULL)
		return mScale;

	Vector2 scale = mParent->Scale(world);
	scale.x *= mScale.x;
	scale.y *= mScale.y;

	return scale;
}

void GameObject::Active(bool active) {

	mActive = active;
}

bool GameObject::Active() {
	return mActive;
}

void GameObject::Parent(GameObject* parent) {

	if (parent == NULL) {
		mPos = Position(world);
		mScale = Scale(world);
		mRotation = Rotation(world);
	}
	else {
		if (mParent != NULL)
			Parent(NULL);

		Vector2 parentScale = parent->Scale(world);

		mPos = RotateVector(Position(world) - parent->Position(world), -parent->Rotation(world));
		mPos.x /= parentScale.x;
		mPos.y /= parentScale.y;

		
		mRotation = mRotation - parent->Rotation(world);

		
		mScale = Vector2(mScale.x / parentScale.x, mScale.y / parentScale.y);

	}

	mParent = parent;
}

GameObject* GameObject::Parent() {
	return mParent;
}


void GameObject::Move(Vector2 vec, SPACE space) {

	if (space == world) {
		mPos += vec;
	}
	else {
		mPos += RotateVector(vec, Rotation());
	}
	
	
}

void GameObject::Rotate(float amount) {

	mRotation += amount;
}

void GameObject::Update() {

}

void GameObject::Render(){



}
