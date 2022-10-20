#pragma once

#include <vector>
#include "Collider.h"

class CollisionObject : public GameObject

{
protected:

	unsigned long mId=0;
	std::vector<Collider*> mCollider;

public:
	CollisionObject();
	virtual ~CollisionObject();

	unsigned long GetId();

	virtual void Render();

protected:
	void AddCollider(Collider* collider, Vector2 localPos=zeroV2);
};

