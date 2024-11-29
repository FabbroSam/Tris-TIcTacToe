#pragma once

enum class GameType { TRIS, TICTACTOE, NONE };

enum class ModType { PvsP, PvsAI, AIvsAI };

enum class Player { RED = 1, BLUE = -1, NONE = 0 };

enum class Turn { PLAYER, AI };

enum class GameState { START, MOVE, END };

enum class BType { RESET, PLAYER, START, VS};

enum class State { RUNNING, GAME, QUIT };