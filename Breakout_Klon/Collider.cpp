#include "Collider.h"

Collider::Collider(ColliderType type) 
	:mType(type)
{
	mTexture = nullptr;

}

Collider::~Collider() {

	if (mTexture) {
		delete mTexture;
		mTexture = NULL;
	}
}

void Collider::SetDebugTexture(Texture* texture) {
	delete mTexture;

	mTexture = texture;
	mTexture->Parent(this);
}

Collider::ColliderType Collider::GetType() {
	return mType;
}

void Collider::Render() {
	if (debug_collider) {
		mTexture->Render();
	}
}