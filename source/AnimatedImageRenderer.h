#pragma once
#include "ImageRenderer.h"
#include <iostream>

class AnimatedImageRenderer : public ImageRenderer
{
private:
	int frameWidth;
	int frameHeight;
	int fps;
	bool looping;
	float currentFrameTime;
	float currentFrame = 0;
	float amountFrames;

public:
	AnimatedImageRenderer(int frameWidth, int frameHeight, int fps, bool looping,
		Transform* transform, std::string resourcePath,
		Vector2 sourceOffset, Vector2 sourceSize)
		: ImageRenderer(transform, resourcePath, sourceOffset, sourceSize),
		frameWidth(frameWidth), frameHeight(frameHeight), fps(fps), looping(looping)
	{
		currentFrameTime = 0;
		amountFrames = sourceRect.w / frameWidth;
	}

	virtual void Update() override
	{
		destRect.x = transform->position.x;
		destRect.y = transform->position.y;

		if (currentFrameTime >= fps)
		{
			currentFrame++;
			currentFrameTime = 0;
		}
		std::cout << currentFrameTime << std::endl;

		if (currentFrame >= amountFrames)
		{
			if (looping)
				currentFrame = 0;
			else
				currentFrame = amountFrames;
		}

		sourceRect.x = frameWidth * currentFrame;
		sourceRect.w = frameWidth;
		sourceRect.h = frameHeight;

		destRect.w = sourceRect.w * transform->scale.x;
		destRect.h = sourceRect.h * transform->scale.y;

		currentFrameTime += TIME.GetDeltaTime();

		ImageRenderer::Update();
	}
	virtual void Render()
	{
		SDL_RenderCopyEx(RM->GetRenderer(), RM->GetTexture(targetPath), &sourceRect, &destRect, transform->rotation, NULL, SDL_FLIP_NONE);
	}
};
