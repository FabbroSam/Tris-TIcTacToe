#include "Board.h"
#include "Object.h"
#include "utils.h"

#include <SDL.h>
#include <SDL_ttf.h>
#include <iostream>

Board::Board(SDL_Renderer* renderer, SDL_FRect rect, int dim)
	: Object(renderer, rect)
{
	_renderer = renderer;
	_rect = rect;
	_dim = dim;
	_type = GameType::NONE;
	_state = GameState::START;
	_player = Player::RED;
	_winner = Player::NONE;

	_matrix = new int* [_dim];
	for (int i = 0; i < _dim; ++i){
		_matrix[i] = new int[_dim];
		for (int j = 0; j < _dim; ++j)
			_matrix[i][j] = 0;
	}

	switch (_dim)
	{
	case 3:
		_type = GameType::TRIS;
		break;

	case 5:
		_type = GameType::TICTACTOE;
		break;

	default:
		std::cout << "Dimensione non supportata!" << std::endl;
		break;
	};
}

void Board::processEvents(SDL_Event& event)
{
	int mouseX, mouseY;
	Uint32 mouseState = SDL_GetMouseState(&mouseX, &mouseY);

	std::cout << "Board:   " << "X: " << mouseX << "Y: " << mouseY << std::endl;

	if (event.type == SDL_MOUSEBUTTONUP) {
		int mouseX = event.button.x;
		int mouseY = event.button.y;


		// Calcola la larghezza e altezza di una singola cella
		float cellWidth = _rect.w / _dim;
		float cellHeight = _rect.h / _dim;

		// Determina l'indice della riga e della colonna
		int col = (mouseX - _rect.x) / cellWidth;
		int row = (mouseY - _rect.y) / cellHeight;

		if (isFreeCell(row, col))
		{
			if (event.button.button == SDL_BUTTON_LEFT) {
				move(row, col);
				std::cout << "(" << row << ", " << col << ")" << std::endl;
			}
		}
	}
}

void Board::render()
{
	SDL_SetRenderDrawColor(_renderer, 200, 200, 200, 255);

	SDL_RenderFillRectF(_renderer, &_rect);

	SDL_SetRenderDrawColor(_renderer, 0, 0, 0, 255);

	int rows_cols = _dim - 1;

	float cellWidth = _rect.w / _dim;
	float cellHeight = _rect.h / _dim;


	// Disegna griglia
	SDL_SetRenderDrawColor(_renderer, 0, 0, 0, 255);
	for (int i = 1; i < _dim; i++) {
		// Linee verticali
		SDL_RenderDrawLineF(_renderer, _rect.x + i * cellWidth, _rect.y, _rect.x + i * cellWidth, _rect.y + _rect.h);
		// Linee orizzontali
		SDL_RenderDrawLineF(_renderer, _rect.x, _rect.y + i * cellHeight, _rect.x + _rect.w, _rect.y + i * cellHeight);
	}

	// Disegna simboli in base a _matrix
	for (int i = 0; i < _dim; i++) {
		for (int j = 0; j < _dim; j++) {
			float centerX = _rect.x + j * cellWidth + cellWidth / 2;
			float centerY = _rect.y + i * cellHeight + cellHeight / 2;

			if (_matrix[i][j] == 1) {
				// Disegna X rossa
				SDL_SetRenderDrawColor(_renderer, 255, 0, 0, 255);
				SDL_RenderDrawLineF(_renderer, centerX - cellWidth / 4, centerY - cellHeight / 4, centerX + cellWidth / 4, centerY + cellHeight / 4);
				SDL_RenderDrawLineF(_renderer, centerX + cellWidth / 4, centerY - cellHeight / 4, centerX - cellWidth / 4, centerY + cellHeight / 4);
			}
			else if (_matrix[i][j] == -1) {
				// Disegna cerchio blu
				SDL_SetRenderDrawColor(_renderer, 0, 0, 255, 255);
				int numSegments = 36;
				for (int k = 0; k < numSegments; k++) {
					float angle1 = k * (2 * M_PI / numSegments);
					float angle2 = (k + 1) * (2 * M_PI / numSegments);
					float x1 = centerX + (cellWidth / 4) * cos(angle1);
					float y1 = centerY + (cellHeight / 4) * sin(angle1);
					float x2 = centerX + (cellWidth / 4) * cos(angle2);
					float y2 = centerY + (cellHeight / 4) * sin(angle2);
					SDL_RenderDrawLineF(_renderer, x1, y1, x2, y2);
				}
			}
		}
	}

	// Disegna la linea del vincitore
	if (_winner != Player::NONE) {
		std::cout << "winner: " << int(_winner) << std::endl;
		SDL_SetRenderDrawColor(_renderer, _winner == Player::RED ? 255 : 0, 0, _winner == Player::RED ? 0 : 255, 255);

		float x1 = _rect.x + _lineWinner[0][0] * cellWidth + cellWidth / 2;
		float y1 = _rect.y + _lineWinner[0][1] * cellHeight + cellHeight / 2;
		float x2 = _rect.x + _lineWinner[1][0] * cellWidth + cellWidth / 2;
		float y2 = _rect.y + _lineWinner[1][1] * cellHeight + cellHeight / 2;

		SDL_RenderDrawLineF(_renderer, x1, y1, x2, y2);
	}

	SDL_SetRenderDrawColor(_renderer, 0, 0, 0, 255);
}

void Board::isWinner()
{
	if (_dim == 3)
	{
		// RIGHE
		for (int i = 0; i < _dim; ++i) {

			if (_matrix[i][0] != 0 &&
				_matrix[i][0] == _matrix[i][1] &&
				_matrix[i][1] == _matrix[i][2]) 
			{
				_lineWinner[0][0] = 0;
				_lineWinner[0][1] = i;
				_lineWinner[1][0] = 2;
				_lineWinner[1][1] = i;
				_winner = Player(_matrix[i][0]); // Vincitore
				_state = GameState::END;
			}
		}
		// COLONNE
		for (int j = 0; j < _dim; ++j) {
			if (_matrix[0][j] != 0 &&
				_matrix[0][j] == _matrix[1][j] &&
				_matrix[1][j] == _matrix[2][j]) 
			{
				_lineWinner[0][0] = j;
				_lineWinner[0][1] = 0;
				_lineWinner[1][0] = j;
				_lineWinner[1][1] = 2;
				_winner = Player(_matrix[0][j]); // Vincitore
				_state = GameState::END;
			}
		}
		// DIAGONALI
		if (_matrix[0][0] != 0 &&
			_matrix[0][0] == _matrix[1][1] &&
			_matrix[1][1] == _matrix[2][2]) 
		{
			_lineWinner[0][0] = 0;
			_lineWinner[0][1] = 0;
			_lineWinner[1][0] = 2;
			_lineWinner[1][1] = 2;
			_winner = Player(_matrix[0][0]); // Vincitore
			_state = GameState::END;
		}

		if (_matrix[0][2] != 0 &&
			_matrix[0][2] == _matrix[1][1] &&
			_matrix[1][1] == _matrix[2][0]) 
		{
			_lineWinner[0][0] = 0;
			_lineWinner[0][1] = 2;
			_lineWinner[1][0] = 2;
			_lineWinner[1][1] = 0;
			_winner = Player(_matrix[0][2]); // Vincitore
			_state = GameState::END;
		}
	}
}

void Board::move(int xCell, int yCell) {

	if (_state == GameState::END || _state == GameState::START && _player != Player::NONE) {
		return;
	}
	if (_player == Player::RED) {
		_matrix[xCell][yCell] = 1;
		_player = Player::BLUE;
	}
	else if (_player == Player::BLUE) {
		_matrix[xCell][yCell] = -1;
		_player = Player::RED;
	}

}

void Board::reset()
{
	_state = GameState::START;
	_winner = Player::NONE;

	for (int i = 0; i < _dim; ++i)
		for (int j = 0; j < _dim; ++j)
			_matrix[i][j] = 0;
}