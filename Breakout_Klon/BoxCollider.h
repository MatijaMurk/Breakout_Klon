#pragma once

#include "Collider.h"

class BoxCollider : public Collider
{
private: 
	static const int maxVertices = 4;
	GameObject* mVertices[maxVertices];

public:
	BoxCollider(Vector2 size);
	~BoxCollider();

	Vector2 GetFurthestPoint() override;

private:
	void AddVert(int index, Vector2 pos);
};

