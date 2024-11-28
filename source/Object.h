#pragma once
#include "Transform.h"
#include "Rigidbody.h"
#include "ImageRenderer.h"
#include "AnimatedImageRenderer.h"
#include "TimeManager.h"

class Object
{
private:
	bool isPendingDestroy;

	Renderer* renderer;

public:
	Transform* transform;
	Rigidbody* physics;

	Object(std::string texturePath, Vector2 sourceOffset, Vector2 sourceSize, bool imageType)
	{
		transform = new Transform();
		physics = new Rigidbody(transform);
		if (!imageType)
		{
			renderer = new ImageRenderer(transform, texturePath, sourceOffset, sourceSize);
		}
		else
		{
			renderer = new AnimatedImageRenderer(128, 64, 1, true, transform, texturePath, sourceOffset, sourceSize);
		}

		isPendingDestroy = false;

	}

	virtual void Update() {
		if(physics != nullptr)
			physics->Update(); 

		renderer->Update();
	}

	virtual void Render()
	{
		renderer->Render();
	}
	Transform* GetTransform() { return transform; }
	Rigidbody* GetRigidBody() { return physics; }
	void SetTransform(Transform* t) { transform = t; }

	// DE MOMENT NO
	/*bool IsPendingDestroy();
	virtual void Destroy();
	virtual void OnCollisionEnter(Object* other);*/
};