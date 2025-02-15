#include "Game.hpp"

#include "Entity.hpp"
#include "PlayerHeli.hpp"

Game::Game() {
}

Game::~Game() {
}

i32 Game::Run() {
	LOG.info("Game {}", "Runs");
	InitGame();

	auto heli = std::make_shared<PlayerHeli>(this);
	heli->SetPosition(100.f, 300.f);
	mPlayer = heli;
	AddEntity(heli);

	while (!WindowShouldClose()) {
		ProcessInput();
		UpdateGame();
		RenderGame();
	}
	Shutdown();
	return 0;
}

void Game::ProcessInput() {
	for (auto &e : mEntitys) {
		e->ProcessInput();
	}
}

void Game::RenderGame() {
	std::vector<std::shared_ptr<Entity>> drawableEntities;
	std::copy(mEntitys.begin(), mEntitys.end(), std::back_inserter(drawableEntities));

	mWindow.BeginDrawing();
	mCamera.BeginMode();
	mWindow.ClearBackground(VIOLET);

	mGameBoundry.Draw(BLACK);
	mGameBoundry.DrawLines(BLUE);

	for (auto &e : drawableEntities) {
		e->Draw();
	}
	mCamera.EndMode();

	// UI
	DrawFPS(20, 20);

	mWindow.EndDrawing();
}

void Game::UpdateGame() {

	for (auto &e : mEntitys) {
		e->Update();
	}

	mCamera.SetTarget(mPlayer->GetPosition());
	mCamera.SetOffset(raylib::Vector2{(GetRenderWidth() / 2) - 100, (GetRenderHeight() / 2) - 50});
	mCamera.SetZoom(1.0);

	// auto pending = [](std::vector<std::shared_ptr<Entity>> pendingVec, std::vector<std::shared_ptr<Entity>> vec) {
	// 	std::move(pendingVec.begin(), pendingVec.end(), std::back_inserter(vec));
	// 	pendingVec.clear();
	// };
	// pending(mPendingEntitys, mEntitys);

	std::move(mPendingEntitys.begin(), mPendingEntitys.end(), std::back_inserter(mEntitys));
	mPendingEntitys.clear();
}

void Game::Shutdown() {
}

void Game::RemoveEntity(std::shared_ptr<Entity> entity) {
	auto removeEntity = [](std::vector<std::shared_ptr<Entity>> vec, std::shared_ptr<Entity> act) {
		auto it = std::find(vec.begin(), vec.end(), act);
		if (it != vec.end())
			vec.erase(it);
	};

	removeEntity(mEntitys, entity);
	removeEntity(mPendingEntitys, entity);
}

void Game::InitGame() {
	mGametitle = "HeliHero";
	SetConfigFlags(FLAG_WINDOW_RESIZABLE);
	mWindow.Init(GAME_SCREEN_WIDTH, GAME_SCREEN_HEIGHT, mGametitle);
	mWindow.SetTargetFPS(60);

	f32 fieldWidth = 5000.f;
	f32 fieldHeight = 1000.f;
	mGameBoundry.SetSize(fieldWidth, fieldHeight);
	mGameBoundry.SetPosition(-(fieldWidth / 2), 0);

	LOG.info("Game Init fertig.");
}