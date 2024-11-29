#include "TextObject.h"
#include "Object.h"
#include "Game.h"
#include "utils.h"

#include <list>
#include <SDL.h>
#include <SDL_ttf.h>
#include <iostream>

TextObject::TextObject(SDL_Renderer* renderer, TTF_Font* font, SDL_FRect rect, SDL_Color color, std::string text)
	: Object(renderer, rect), _renderer(renderer), _font(font), _rect(rect), _color(color), _text(text)
{
	if (text == "Reset")
		_type = BType::RESET;
	else if (text == "Player")
		_type = BType::PLAYER;
	else if (text == "Start")
		_type = BType::START;
	else if (text == "P vs AI")
		_type = BType::VS;
}

void TextObject::render()
{

	SDL_SetRenderDrawColor(_renderer, 200, 200, 200, 255);

	SDL_RenderFillRectF(_renderer, &_rect);

	SDL_SetRenderDrawColor(_renderer, _color.r, _color.g, _color.b, _color.a);


	SDL_Surface* textSurface = TTF_RenderText_Blended(_font, _text.c_str(), _color);
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

void TextObject::update()
{
	Board* board = Game::instance()->board();
	if (_type == BType::START)
	{
		if (board->state() == GameState::START || board->state() == GameState::END)
			_color = { 0,0,0,255 };
		else
			_color = { 0,255,0,255 };
	}
	else if (_type == BType::PLAYER)
	{
		if (board->player() == Player::RED)
			_color = { 255,0,0,255 };
		else if (board->player() == Player::BLUE)
			_color = { 0,0,255,255 };
	}
}

void TextObject::processEvents(SDL_Event& event)
{
	int mouseX, mouseY;
	Uint32 mouseState = SDL_GetMouseState(&mouseX, &mouseY);
	std::cout << _text <<":   " << "X: " << mouseX << "Y: " << mouseY << std::endl;

	if (event.type == SDL_MOUSEBUTTONUP) {
		int mouseX = event.button.x;
		int mouseY = event.button.y;

		Board* board = Game::instance()->board();
		switch (_type)
		{
		case BType::RESET:
			board->reset();
			break;
		case BType::START:
			if (board->state() == GameState::START)
				board->setState(GameState::MOVE);
		case BType::PLAYER:
			if (board->state() == GameState::START)
			{
				if (board->player() == Player::RED)
					board->setPlayer(Player::BLUE);
				else if (board->player() == Player::BLUE)
					board->setPlayer(Player::RED);
				Game::instance()->setState(State::GAME);
			}
			break;
		case BType::VS:
			if (board->state() == GameState::START)
			{
				if (Game::instance()->modType() == ModType::PvsAI)
				{
					_text = "P vs P";
					Game::instance()->setModType(ModType::PvsP);
				}
				else if (Game::instance()->modType() == ModType::PvsP)
				{
					_text = "AI vs AI";
					Game::instance()->setModType(ModType::AIvsAI);
				}
				else if (Game::instance()->modType() == ModType::AIvsAI)
				{
					_text = "P vs AI";
					Game::instance()->setModType(ModType::PvsAI);
				}
			}
			break;
		}
	}
}