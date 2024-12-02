#pragma once
#include "Transform.h"
#include "Rigidbody.h"
#include "ImageRenderer.h"
#include "AnimatedImageRenderer.h"
#include "TimeManager.h"

class Object
{
private:
	bool isPendingDestroy = false;

	Renderer* renderer;
protected:
	Transform* transform;
	Rigidbody* physics;
public:



	Object(std::string texturePath, Vector2 sourceOffset, Vector2 sourceSize, bool imageType)
	{
		transform = new Transform();
		physics = new Rigidbody(transform);
		physics->AddCollider(new AABB(sourceOffset, sourceSize * 0.2f)); 
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

	~Object() {
		delete transform; 
		delete physics;
		delete renderer; 
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
	bool IsPendingDestroy() const { return isPendingDestroy;  }
	virtual void Destroy() { isPendingDestroy = true;  }
	virtual void OnCollisionEnter(Object* other) {}
};