#pragma once
#include "Object.h"
#include "AnimatedImageRenderer.h"

class AnimatedImageObject : public Object {
public:
	AnimatedImageObject(std::string texturePath, Vector2 sourceOffset, Vector2 sourceSize)
		: Object() {
		physics->AddCollider(new AABB(sourceOffset, sourceSize * 0.2f));
		renderer = new AnimatedImageRenderer(128, 64, 1, true, transform, texturePath, sourceOffset, sourceSize);
		Object::Update();
	}
};