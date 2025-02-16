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

	// mCamera.zoom += ((f32)GetMouseWheelMove() * 0.05f);
	// if (mCamera.zoom < 0.1f)
	// 	mCamera.zoom = 0.1f;
	// if (mCamera.zoom > 7.f)
	// 	mCamera.zoom = 7.f;
}

void Game::RenderGame() {
	std::vector<std::shared_ptr<Entity>> drawableEntities;
	std::copy(mEntitys.begin(), mEntitys.end(), std::back_inserter(drawableEntities));

	static auto ground = raylib::Rectangle{mGameBoundry.GetPosition(), mGameBoundry.GetSize()};
	ground.SetHeight(10);
	ground.SetY(mGameBoundry.height - ground.height);

	mWindow.BeginDrawing();
	mCamera.BeginMode();
	mWindow.ClearBackground(VIOLET);

	mGameBoundry.Draw(BLACK);
	ground.Draw(GREEN);

	for (i32 x = mGameBoundry.x; x < mGameBoundry.width - mGameBoundry.x; x += 100) {
		DrawRectangle(x - 1, ground.y - 5, 2, 5, BLUE);
	}

	for (auto &e : drawableEntities) {
		e->Draw();
	}

	mGameBoundry.DrawLines(BLUE);

	mCamera.EndMode();

	// UI
	DrawFPS(20, 20);
	mWindow.EndDrawing();
}

void Game::UpdateCamera() {
	mCamera.SetTarget(mPlayer->GetPosition());

	const auto size = mWindow.GetSize();
	const auto offset = raylib::Vector2(size.x / 2.f, size.y / 2.f);
	mCamera.SetOffset(offset);

	const f32 zoomFactor = 1.0f / mCamera.zoom / 2.0f;

	const f32 viewportX = size.x * zoomFactor;
	const f32 viewportY = size.y * zoomFactor;

	const f32 minX = mGameBoundry.x + viewportX;
	const f32 minY = mGameBoundry.y + viewportY;

	const f32 maxX = mGameBoundry.width - viewportX;
	const f32 maxY = mGameBoundry.height - viewportY;

	mCamera.target.x = std::clamp(mCamera.target.x, minX, maxX);
	mCamera.target.y = std::clamp(mCamera.target.y, minY, maxY);
}

void Game::UpdateGame() {

	for (auto &e : mEntitys) {
		e->Update();
	}

	UpdateCamera();

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

	f32 fieldWidth = 500.f;
	f32 fieldHeight = 100.f;
	mGameBoundry.SetSize(fieldWidth, fieldHeight);
	// mGameBoundry.SetPosition(-(fieldWidth / 2), 0);
	mGameBoundry.SetPosition(0.f, 0.f);

	mCamera.SetZoom(7.0);

	auto heli = std::make_shared<PlayerHeli>(this);
	heli->SetPosition(fieldWidth / 2, fieldHeight / 2);
	mPlayer = heli;
	AddEntity(heli);

	LOG.info("Game Init fertig.");
}