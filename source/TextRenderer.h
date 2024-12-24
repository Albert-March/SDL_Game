#pragma once
#include "SDL.h" // SDL_Textur*
#include "SDL_ttf.h" // SDL

#include "Renderer.h"
#include "RenderManager.h"

#define FONT_PATH "resources/fonts/PixelPowerline-9xOK.ttf"

class TextRenderer : public Renderer {
protected:
	std::string text;
	SDL_Texture* textTexture;
	bool autoSize = true;

public:
	TextRenderer(Transform* transform, std::string _text)
		:Renderer(transform, FONT_PATH) {
		SetText(_text);
	}

	void SetColor(SDL_Color color) override {
		Renderer::SetColor(color);
		SetText(text);
	}

	virtual void Update() override {
		Vector2 offset = (Vector2(-transform->size.x, -transform->size.y) / 2.0f) * transform->scale;

		destRect.x = transform->position.x + offset.x;
		destRect.y = transform->position.y + offset.y;

		if (autoSize) {
			destRect.w = sourceRect.w * transform->scale.x;
			destRect.h = sourceRect.h * transform->scale.y;
		}
		else {

			destRect.w = transform->size.x * transform->scale.x;
			destRect.h = transform->size.y * transform->scale.y;
		}
	}

	virtual void Render()
	{
		SDL_RenderCopyEx(RM->GetRenderer(), textTexture, &sourceRect, &destRect, transform->rotation, NULL, SDL_FLIP_NONE);
	}

	void SetText(std::string newText) {
		RM->LoadFont(targetPath);

		//Generate the texture
		if (textTexture != nullptr)
			SDL_DestroyTexture(textTexture);

		TTF_Font* font = RM->GetFont(targetPath);

		// Per poder dividir el text en lineas
		std::vector<std::string> lines;
		size_t start = 0;
		size_t end = newText.find('\n');
		while (end != std::string::npos) {
			lines.push_back(newText.substr(start, end - start));
			start = end + 1;
			end = newText.find('\n', start);
		}
		lines.push_back(newText.substr(start));

		//Renderitzar i calcular dimensions de cada linea
		int totalHeight = 0;
		int maxWidth = 0;
		std::vector<SDL_Surface*> lineSurfaces;

		for (const auto& line : lines) {

			if (line.empty()) {
				std::cout << "Línea vacía detectada, saltando..." << std::endl;
				continue;
			}

			SDL_Surface* lineSurface = TTF_RenderText_Solid(
				font,
				line.c_str(),
				color
			);

			/*if (!lineSurface) {
				std::cerr << "Error: No se pudo renderizar la línea: '" << line
					<< "' SDL_ttf Error: " << TTF_GetError() << std::endl;
				continue;
			}*/

			totalHeight += lineSurface->h;
			maxWidth = std::max(maxWidth, lineSurface->w);
			lineSurfaces.push_back(lineSurface);
		}

		//Crear superficia
		SDL_Surface* finalSurface = SDL_CreateRGBSurface(0, maxWidth, totalHeight, 32, 0, 0, 0, 0);
		if (!finalSurface) {
			std::cerr << "Error: No se pudo crear la superficie final. SDL_Error: " << SDL_GetError() << std::endl;
			return;
		}

		int yOffset = 0;
		for (SDL_Surface* lineSurface : lineSurfaces) {
			SDL_Rect destRect = { 0, yOffset, lineSurface->w, lineSurface->h };
			SDL_BlitSurface(lineSurface, nullptr, finalSurface, &destRect);
			yOffset += lineSurface->h;
			SDL_FreeSurface(lineSurface); // Liberar superficie de línea
		}

		//Crear Textura
		textTexture = SDL_CreateTextureFromSurface(RM->GetRenderer(), finalSurface);
		if (!textTexture) {
			std::cerr << "Error: No se pudo crear la textura final. SDL_Error: " << SDL_GetError() << std::endl;
			SDL_FreeSurface(finalSurface);
			return;
		}

		sourceRect = {
			0,0,
			finalSurface->w, finalSurface->h
		};

		SDL_FreeSurface(finalSurface);
		text = newText;
	}

	SDL_Rect GetSourceRect() const {
		return sourceRect;
	}

	SDL_Rect GetDestRect() const {
		return destRect;
	}
};
