#pragma once
#include "GameObject.h"
#include "Texture.h"

class Collider:public GameObject
{

public:
	enum class ColliderType {
		Box,
		Circle
	};
protected:
	ColliderType mType;

	static const bool debug_collider = true;
	Texture* mTexture;


public:
	Collider(ColliderType type);
	virtual ~Collider();
	
	virtual Vector2 GetFurthestPoint() = 0;

	ColliderType GetType();

	
	virtual void Render();

protected:
	void SetDebugTexture(Texture* texture);

};

