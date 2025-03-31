#include "Game.hpp"

#include "Entity.hpp"

#include <format>

namespace {
constexpr f32 GROUND_HEIGHT = 20.f;

constexpr f32 FIELD_WIDTH = 500.f;
constexpr f32 FIELD_HEIGHT = 100.f;
} // namespace

Game::Game() {
}

Game::~Game() {
}

i32 Game::Run() {
	log->info("Game {}", "Runs");
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
	auto mouse = GetMousePosition();

	mouse = mCamera.GetScreenToWorld(mouse);

	mWindow.BeginDrawing();
	mCamera.BeginMode();
	mWindow.ClearBackground(VIOLET);

	mGameBoundry.Draw((Color){160, 185, 186, 255});
	mGroundRect.Draw((Color){119, 116, 79, 255});

	for (i32 x = mGameBoundry.x; x < mGameBoundry.width - mGameBoundry.x; x += 100) {
		DrawRectangle(x - 1, mGroundRect.y - 5, 2, 5, BLUE);
	}

	for (auto &e : drawableEntities) {
		e->Draw();
	}

	mGameBoundry.DrawLines(BLUE);

	mCamera.EndMode();

	// UI

	DrawFPS(20, 20);
	auto [mX, mY] = GetMousePosition();
	DrawText(std::format("{} {}", mX, mY).c_str(), 20, 40, 4, RED);

	mWindow.EndDrawing();
}

void Game::UpdateCamera() {

	const auto size = mWindow.GetSize();
	const auto offset = raylib::Vector2(size.x / 2.f, size.y / 2.f);
	mCamera.SetOffset(offset);

	mCamera.SetTarget(raylib::Vector2(20.f, 1.f));
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
		if (e->CheckGroundCollision(mGroundRect)) {
			e->OnGroundCollision(mGroundRect);
		}
		if (
			e->CheckMapBoundryCollision(mGameBoundry)) {
			e->OnMapBoundryCollision(mGameBoundry);
		}
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

	SpriteManager::Init("assets/Sprite-0001.png");
	AnimationManager::Init();

	mGameBoundry.SetSize(FIELD_WIDTH, FIELD_HEIGHT);
	// mGameBoundry.SetPosition(-(FIELD_WIDTH / 2), 0);
	mGameBoundry.SetPosition(0.f, 0.f);

	mGroundRect = raylib::Rectangle{mGameBoundry.GetPosition(), mGameBoundry.GetSize()};
	mGroundRect.SetHeight(GROUND_HEIGHT);
	mGroundRect.SetY(mGameBoundry.height - mGroundRect.height);

	mCamera.SetZoom(7.0);
	AddUnit(Unit::Type::Soldier, {20, 20});
	AddUnit(Unit::Type::Orc, {40, 20});

	log->info("Game Init fertig.");
}

void Game::AddUnit(Unit::Type type, raylib::Vector2 pos) {
	auto ptr = std::make_shared<Unit>(this, type);
	ptr->SetPosition(pos);
	AddEntity(std::move(ptr));
}