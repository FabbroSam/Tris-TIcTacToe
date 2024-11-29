#pragma once
#include "Object.h"

#include <SDL.h>
#include <SDL_ttf.h>

#include <iostream>

enum class BType {RESET};

class TextObject : public Object
{
protected:
	SDL_Renderer* _renderer;
	TTF_Font* _font;
	SDL_FRect _rect;
	SDL_Color _color;
	char* _text;
	BType _type;

public:
	TextObject(SDL_Renderer* renderer, TTF_Font* font, SDL_FRect rect, SDL_Color color, char* text);

	// game rendering
	virtual void render();
	virtual void update() {};
	virtual void processEvents(SDL_Event& event);

};