#include "CircleCollider.h"

CircleCollider::CircleCollider(float radius, bool broadPhase) 
	:Collider(ColliderType::Circle) {

	mRadius = radius;

	SetDebugTexture(new Texture("CircleCollider.png"));

	mTexture->Scale(oneV2 * (radius * 2 / 100.0f));

}

CircleCollider::~CircleCollider() {

}

Vector2 CircleCollider::GetFurthestPoint() {

	return Vector2(1.0f, 0.0f) * (mRadius + Position(GameObject::local).Magnitude());
}
