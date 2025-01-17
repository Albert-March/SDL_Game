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
    float currentFrameTime = 0.0f;
    int currentColumn = 0;
    int currentRow = 0;
    int numRows;
    int numColumns;
    float frameDuration;

public:
    AnimatedImageRenderer(int numRows, int numColumns, int fps, bool looping, Transform* transform, std::string resourcePath, Vector2 sourceOffset, Vector2 sourceSize)
        : ImageRenderer(transform, resourcePath, sourceOffset, sourceSize), numRows(numRows), numColumns(numColumns), fps(fps), looping(looping)
    {
        frameWidth = sourceSize.x / numRows;
        frameHeight = sourceSize.y / numColumns;

        frameDuration = 10.0f / fps;
    }

    virtual void Update() override
    {
        destRect.x = transform->position.x;
        destRect.y = transform->position.y;

        currentFrameTime += TIME.GetDeltaTime();

        if (currentFrameTime >= frameDuration)
        {
            currentFrameTime -= frameDuration;

            currentColumn++;

            if (currentColumn >= numColumns)
            {
                currentColumn = 0;
                currentRow++;

                if (currentRow >= numRows)
                {
                    if (looping)
                    {
                        currentRow = 0;
                    }
                    else
                    {
                        currentRow = numRows - 1;
                        currentColumn = numColumns - 1;
                    }
                }
            }
        }

        sourceRect.x = frameWidth * currentColumn;
        sourceRect.y = frameHeight * currentRow;
        sourceRect.w = frameWidth;
        sourceRect.h = frameHeight;

        destRect.w = sourceRect.w * transform->scale.x;
        destRect.h = sourceRect.h * transform->scale.y;

        ImageRenderer::Update();
    }
	virtual void Render()
	{
		SDL_RenderCopyEx(RM->GetRenderer(), RM->GetTexture(targetPath), &sourceRect, &destRect, transform->rotation, NULL, SDL_FLIP_NONE);
	}
};
