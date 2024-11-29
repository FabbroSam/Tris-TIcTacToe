#include "Game.h"

#include "Object.h"
#include "TextObject.h"
#include "Board.h"

#include <SDL.h>
#include <SDL_ttf.h>

#include <list>
#include <iostream>

Game* Game::instance()
{
	static Game uniqueInstance;
	return &uniqueInstance;
}

Game::Game() :
	_window(nullptr),
	_renderer(nullptr),
	_font(nullptr)
{
	init();
	initObjects();
	reset();
}

void Game::init()
{

	SDL_Init(SDL_INIT_VIDEO);

	// Creazione della finestra principale
	_window = SDL_CreateWindow(
		"HelloWorld",				// Window title
		SDL_WINDOWPOS_CENTERED,		// Top left x-coordinate of window
		SDL_WINDOWPOS_CENTERED,		// Top left y-coordinate of window
		800,						// Width of window
		600,						// Height of window
		0							// Flags (0 for no flags set)
	);

	// Inizializza SDL_ttf
	TTF_Init();

	_renderer = SDL_CreateRenderer(
		_window,					// Window to create renderer for
		-1,							// Usually -1
		SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC
	);

	// Carica il font una sola volta (meglio farlo nel costruttore del gioco e chiuderlo nel distruttore)
	_font = TTF_OpenFont("C:/Windows/Fonts/Verdana.ttf", 24);
	if (!_font) {
		std::cerr << "Errore nel caricamento del font: " << TTF_GetError() << std::endl;
		return;
	}
}
void Game::initObjects()
{
	_objects.push_back(new TextObject(_renderer, _font, { 0,0,100,25 }, { 0,0,0,255 }, "Menu"));
	_objects.push_back(new TextObject(_renderer, _font, { 100,0,100,25 }, { 0,0,0,255 }, "Type"));
	_board = new Board(_renderer, { 50,150,400,400 }, 3);
	_objects.push_back(_board);
}
void Game::run()
{

	while (_state != State::QUIT)
	{
		processEvents();
		update();
		render();
	}

	quit();
}

void Game::quit()
{
	SDL_DestroyRenderer(_renderer);
	SDL_DestroyWindow(_window);
	SDL_Quit();
}

void Game::reset()
{
	_state = State::RUNNING;
}


void Game::processEvents()
{
	SDL_Event event;
	while (SDL_PollEvent(&event))
	{
		if (event.type == SDL_QUIT)
			_state = State::QUIT;
		else
			for (const auto& obj : _objects)
				obj->processEvents(event);
	}

	const Uint8* state = SDL_GetKeyboardState(0);
	if (state[SDL_SCANCODE_ESCAPE])
		_state = State::QUIT;
	else if (state[SDL_SCANCODE_UP])
		;
	else if (state[SDL_SCANCODE_DOWN])
		;
	else if (state[SDL_SCANCODE_RIGHT])
		;
	else if (state[SDL_SCANCODE_LEFT])
		;
	else if (state[SDL_SCANCODE_SPACE])
		;

}

void Game::update()
{
	for (const auto& obj : _objects)
		obj->update();
}

void Game::render() {

	// Pulisci il buffer
	SDL_RenderClear(_renderer);

	for (const auto& obj : _objects)
		obj->render();

	// Mostra tutto sullo schermo
	SDL_RenderPresent(_renderer);
}
