#include "Game.hpp"

Game::Game() {
}

Game::~Game() {
}

i32 Game::Run() {
	Logger logger;
	logger.info("Game {}", "Runs.");
	return 0;
}