#pragma once
#include "Object.h"
#include "AnimatedImageRenderer.h"

class AnimatedImageObject : public Object {
public:
	AnimatedImageObject(std::string texturePath, Vector2 sourceOffset, Vector2 sourceSize, int numRows, int numColumns, bool looping)
		: Object() {
		physics->AddCollider(new AABB(sourceOffset, sourceSize * 0.2f));
		renderer = new AnimatedImageRenderer(numRows, numColumns, 60, looping, transform, texturePath, sourceOffset, sourceSize);
		Object::Update();
	}
};