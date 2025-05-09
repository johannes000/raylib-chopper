#pragma once
#include "Utility\Includes.hpp"
#include "Utility\AnimationManager.hpp"
#include "Units\Unit.hpp"

class Entity;

class Game {
public:
	Game();
	~Game();

	i32 Run();
	void InitGame();
	void ProcessInput();
	void RenderGame();
	void UpdateGame();
	void UpdateCamera();
	void Shutdown();

	void AddUnit(Unit::Type type, raylib::Vector2 pos);
	auto GetGroundRect() { return mGroundRect; }

	template <typename T>
	Entity *AddEntity(std::shared_ptr<T> entity) {
		if (!std::is_base_of_v<Entity, T>) {
			log->warn("T muss von Entity vererbt sein");
			return nullptr;
		}
		// auto castEntity = std::static_pointer_cast<Entity>(entity);
		auto rawPtr = entity.get();
		mPendingEntitys.emplace_back(std::move(entity));
		return rawPtr;
	}
	void RemoveEntity(std::shared_ptr<Entity> Entity);

private:
	std::string mGametitle;

	raylib::Window mWindow;
	raylib::Camera2D mCamera{};

	std::shared_ptr<class PlayerHeli> mPlayer;

	std::vector<std::shared_ptr<Entity>> mEntitys;
	std::vector<std::shared_ptr<Entity>> mPendingEntitys;

	raylib::Rectangle mGameBoundry;
	raylib::Rectangle mGroundRect;

private:
	LogPtr log = spdlog::get("GAM");
};
