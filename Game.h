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
		State _state;
		ModType _type;
		Turn _turn;

	// Object
		std::list<Object*> _objects;
		
	// Board
		Board* _board;

	// Button
		TextObject* _whoMove;

	// Costruttore	
		Game();

	public: 
		
		// singleton
		static Game* instance();

		//get/set
		std::list<Object*> objects() { return _objects; }
		Board* board() { return _board; }
		State state() { return _state; }
		void setState(State st) { _state = st; }
		void setModType(ModType type) { _type = type; }
		ModType modType() { return _type; }

		// action
		void run();
		void reset();

		// Modality
		void playerVsAi();
		void playerVsPlayer();
		void aiVsAi();

};