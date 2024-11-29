#include "TextObject.h"
#include "Object.h"
#include "Game.h"

#include <list>
#include <SDL.h>
#include <SDL_ttf.h>
#include <iostream>

TextObject::TextObject(SDL_Renderer* renderer, TTF_Font* font, SDL_FRect rect, SDL_Color color, char* text)
	: Object(renderer, rect), _renderer(renderer), _font(font), _rect(rect), _color(color), _text(text)
{
	if (_text == "Reset")
	{
		_type = BType::RESET;
	}
}

void TextObject::render()
{

	SDL_SetRenderDrawColor(_renderer, 200, 200, 200, 255);

	SDL_RenderFillRectF(_renderer, &_rect);

	SDL_SetRenderDrawColor(_renderer, _color.r, _color.g, _color.b, _color.a);

	SDL_Surface* textSurface = TTF_RenderText_Blended(_font, _text, _color);
	if (!textSurface) {
		std::cerr << "Errore nella creazione della superficie di testo: " << TTF_GetError() << std::endl;
		return;
	}

	SDL_Texture* textTexture = SDL_CreateTextureFromSurface(_renderer, textSurface);
	if (!textTexture) {
		std::cerr << "Errore nella creazione della texture di testo: " << SDL_GetError() << std::endl;
		SDL_FreeSurface(textSurface);
		return;
	}

	float x = 0.25f * _rect.w;
	float y = 0.1f * _rect.h;
	SDL_FRect textRect = { _rect.x + x, _rect.y + y,_rect.w - 2 * x, _rect.h - 2 * y };

	SDL_RenderCopyF(_renderer, textTexture, NULL, &textRect);

	SDL_RenderDrawRectF(_renderer, &_rect);

}


void TextObject::processEvents(SDL_Event& event)
{
	int mouseX, mouseY;
	Uint32 mouseState = SDL_GetMouseState(&mouseX, &mouseY);

	// Verifica se il mouse è all'interno del rettangolo del board
	if ((mouseX > _rect.x) && (mouseX < _rect.x + _rect.w) &&
		(mouseY > _rect.y) && (mouseY < _rect.y + _rect.h))
	{
		std::cout << _text <<":   " << "X: " << mouseX << "Y: " << mouseY << std::endl;

		if (event.type == SDL_MOUSEBUTTONUP) {
			int mouseX = event.button.x;
			int mouseY = event.button.y;

			if (_type == BType::RESET)
			{

			}
		}
		
	}
}