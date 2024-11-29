#pragma once
#include "Object.h"

enum class GameType { TRIS, TICTACTOE };
enum class Player { RED = 1, BLUE =  -1, NONE = 0};
enum class GameState { START, MOVERED, MOVEBLUE, END};

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
		Player _winner;
		int _lineWinner[2][2];

	public:
		Board(SDL_Renderer* renderer, SDL_FRect rect, int dim);

		// rendering
		virtual void processEvents(SDL_Event& event);
		virtual void update() { isWinner(); };
		virtual void render() ;

		// action
		bool isFreeCell(int xCell, int yCell) { return !_matrix[xCell][yCell]; }
		void isWinner();
		void moveBlue(int xCell, int yCell) { (_state == GameState::START || _state == GameState::MOVEBLUE) ? (_matrix[xCell][yCell] = -1) : false; };
		void moveRed(int xCell, int yCell) { (_state == GameState::START || _state == GameState::MOVEBLUE) ? (_matrix[xCell][yCell] = 1) : false; };

};
