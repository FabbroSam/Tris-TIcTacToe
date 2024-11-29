#pragma once
#include "Object.h"
#include "utils.h"


class Board : public Object
{
	protected:
		SDL_Renderer* _renderer;
		SDL_FRect _rect;

		int _dim;
		int** _matrix;
		GameType _type;
		GameState _state;

		//logic game
		Player _player;
		Player _winner;
		int _lineWinner[2][2]{0};

	public:
		Board(SDL_Renderer* renderer, SDL_FRect rect, int dim);

		// rendering
		virtual void processEvents(SDL_Event& event);
		virtual void update() { isWinner(); };
		virtual void render() ;

		//get/set
		GameState state() { return _state; };
		void setState(GameState state) { _state = state; };
		Player player() { return _player; };
		void setPlayer(Player player) { _player = player; };

		// action
		bool isFreeCell(int xCell, int yCell) { return !_matrix[xCell][yCell]; }
		void isWinner();
		void move(int xCell, int yCell);
		void reset();
};
