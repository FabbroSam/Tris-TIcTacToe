#pragma once
#include "Object.h"
#include "utils.h"

#include <SDL.h>
#include <SDL_ttf.h>

#include <iostream>
#include <string>


class TextObject : public Object
{
protected:
	SDL_Renderer* _renderer;
	TTF_Font* _font;
	SDL_FRect _rect;
	SDL_Color _color;
	std::string _text;
	BType _type;

public:
	TextObject(SDL_Renderer* renderer, TTF_Font* font, SDL_FRect rect, SDL_Color color, std::string text);

	//get/set
	void setColor(SDL_Color color) { if(_type == BType::PLAYER) _color = color; };

	// game rendering
	virtual void render();
	virtual void update();
	virtual void processEvents(SDL_Event& event);

};