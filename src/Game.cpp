#include "Game.hpp"

Game::Game() {
}

Game::~Game() {
}

i32 Game::Run() {
	LOG.info("Game {}", "Runs");
	InitGame();

	while (!WindowShouldClose()) {
		ProcessInput();
		UpdateGame();
		RenderGame();
	}
	Shutdown();
	return 0;
}

void Game::ProcessInput() {
}

void Game::RenderGame() {
	mWindow.BeginDrawing();
	{
		mWindow.ClearBackground(VIOLET);
		auto text = raylib::Text(mGametitle, 80, RED);
		text.Draw((GetScreenWidth() / 2) - (text.Measure() / 2), GetScreenHeight() / 2);
	}
	mWindow.EndDrawing();
}

void Game::UpdateGame() {
}

void Game::Shutdown() {
}

void Game::InitGame() {
	mGametitle = "HeliHero";
	SetConfigFlags(FLAG_WINDOW_RESIZABLE);
	mWindow.Init(GAME_SCREEN_WIDTH, GAME_SCREEN_HEIGHT, mGametitle);
	mWindow.SetTargetFPS(60);

	LOG.info("Game Init fertig.");
}