#include "CollisionObject.h"

CollisionObject::CollisionObject(){}

CollisionObject::~CollisionObject(){
	for (int i = 0; i < mCollider.size(); i++) {
		delete mCollider[i];
		mCollider[i] = nullptr;
 }

	mCollider.clear();
}

unsigned long CollisionObject::GetId()
{
	return mId;
}

void CollisionObject::AddCollider(Collider* collider, Vector2 localPos) {
	
	collider->Parent(this);
	collider->Position(localPos);
	mCollider.push_back(collider);
}

void CollisionObject::Render(){

	for (int i = 0; i < mCollider.size(); i++) {
		mCollider[i]->Render();
	}

}
