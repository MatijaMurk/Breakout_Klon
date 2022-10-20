#pragma once

#include "CollisionObject.h"
#include <bitset>

class CollisionManager
{
public:
	enum class CollisionLayers {
		Player,
		Ball,
		Brick,
		AllLayers
	};

	enum class CollisionFlags {

		None = 0x00,
		Player = 0x01,
		Ball = 0x02,
		Brick = 0x04

	};


private:

	static CollisionObject* sInstance;

	std::vector <CollisionObject*>mCollisionLayers[static_cast<unsigned int>(CollisionLayers::AllLayers)];
	std::bitset<static_cast<unsigned int>(CollisionLayers::AllLayers)>mLayerMasks[static_cast<unsigned int>(CollisionLayers::AllLayers)];

	unsigned long mLastId;

public:

	static CollisionManager* Instance();
	static void Release();

	//void SetLayer


};

