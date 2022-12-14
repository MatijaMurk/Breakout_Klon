#include "BoxCollider.h"

BoxCollider::BoxCollider(Vector2 size)
	: Collider(ColliderType::Box)
{
	AddVert(0, Vector2(-0.5f * size.x, -0.5f * size.y));
	AddVert(1, Vector2(0.5f * size.x, -0.5f * size.y));
	AddVert(2, Vector2(-0.5f * size.x, 0.5f * size.y));
	AddVert(3, Vector2(0.5f * size.x, 0.5f * size.y));

	if (debug_collider) {
		SetDebugTexture(new Texture("BoxCollider.png"));
		mTexture->Scale(size / 100.0f);
	}
}

BoxCollider::~BoxCollider() {

	for (int i = 0; i < maxVertices; i++) {
		delete mVertices[i];
		mVertices[i] = nullptr;
	}
}

Vector2 BoxCollider::GetFurthestPoint() {
	return zeroV2;
}

void BoxCollider::AddVert(int index, Vector2 pos) {
	mVertices[index] = new GameObject(pos);
	mVertices[index]->Parent(this);
}
