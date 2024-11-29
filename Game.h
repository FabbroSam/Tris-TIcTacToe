#pragma once
#include "Object.h"
#include "TextObject.h"
#include "Board.h"

#include <SDL.h>
#include <SDL_ttf.h>

#include <list>
#include <iostream>

class Game
{ 
	// game rendering
	protected:

		SDL_Window* _window;
		SDL_Renderer* _renderer;
		TTF_Font* _font;

		void init();
		void initObjects();
		void processEvents();
		void update();
		void render();
		void quit();

	// game logic

		enum class State { RUNNING, QUIT };

		State _state;
		void reset();

	// Object
		std::list<Object*> _objects;
		
	// Board
		Board* _board;

	// Costruttore	
		Game();

	public: 
		
		// singleton
		static Game* instance();

		void run();

		//get/set
		std::list<Object*> objects() { return _objects; }
};