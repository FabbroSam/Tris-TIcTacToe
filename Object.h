#pragma once
#include <SDL.h>
#include <SDL_ttf.h>

class Object
{
	protected:
		SDL_Renderer* _renderer;
		SDL_FRect _rect;

	public:
		Object(SDL_Renderer* renderer, SDL_FRect rect) : _renderer(renderer), _rect(rect) {}

		// game rendering
		virtual void processEvents(SDL_Event& event) = 0;
		virtual void update() = 0;
		virtual void render() = 0;
};


