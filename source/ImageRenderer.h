#pragma once
#include "Renderer.h"
#include "RenderManager.h"

class ImageRenderer : public Renderer
{
public:
	ImageRenderer(Transform* transform, std::string resourcePath, Vector2 sourceOffset, Vector2 sourceSize)
		: Renderer(transform, resourcePath) 
	{
		RM->LoadTexture(resourcePath);

		sourceRect = SDL_Rect
		{
			(int)sourceOffset.x,
			(int)sourceOffset.y,
			(int)sourceSize.x,
			(int)sourceSize.y
		};

		destRect = SDL_Rect
		{
			(int)transform->position.x,
			(int)transform->position.y,
			(int)transform->scale.x,
			(int)transform->scale.y
		};
	}
	virtual void Update() override
	{
		destRect.x = transform->position.x;
		destRect.y = transform->position.y;

		destRect.w = sourceRect.w * transform->scale.x;
		destRect.h = sourceRect.h * transform->scale.y;
	}

	virtual void Render()
	{
		SDL_RenderCopy(RM->GetRenderer(), RM->GetTexture(targetPath), &sourceRect, &destRect);
	}
};