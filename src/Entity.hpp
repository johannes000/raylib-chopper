#pragma once

#include "Utility\Includes.hpp"
#include <array>

class Game;

enum Category {
	Enemy = 1 << 0,
	Friendly = 1 << 1,
};

struct CollisionData {
	raylib::Rectangle CollisionRect{};
	raylib::Vector2 CollisionRectOffset{};
};

class Entity {
public:
	enum struct State {
		Active,
		Paused,
		Dead
	};

	typedef std::shared_ptr<Entity> Ptr;
	typedef std::unique_ptr<Entity> UPtr;

	Entity(Game *game);
	virtual ~Entity();

	void Update();
	virtual void UpdateEntity(); // Entity Spezifisches update
	virtual void Draw() const;
	virtual void ProcessInput();

	virtual bool CheckGroundCollision(raylib::Rectangle groundRect); // return true bei Kollision
	virtual bool CheckMapBoundryCollision(raylib::Rectangle bounds); // return true bei Kollision

	virtual void OnGroundCollision(raylib::Rectangle groundRect);
	virtual void OnMapBoundryCollision(raylib::Rectangle bounds);

	virtual CollisionData GetCurrentCollisionData() const;
	virtual void UpdateCollisionData();

	std::array<raylib::Vector2, 4> GetTransformedCollisionRect() const;

	State GetState() const { return mState; }
	void SetState(State state) { mState = state; }

	const raylib::Vector2 GetPosition() const { return mPosition; }
	void SetPosition(raylib::Vector2 pos) { mPosition = pos; }
	void SetPosition(f32 x, f32 y) { mPosition = raylib::Vector2{x, y}; }

	const raylib::Vector2 GetVelocity() const { return mVelocity; }
	void SetVelocity(raylib::Vector2 vel) { mVelocity = vel; }
	void SetVelocity(f32 x, f32 y) { mVelocity = raylib::Vector2{x, y}; }

	f32 GetScale() const { return mScale; }
	void SetScale(f32 scale) { mScale = scale; }

	f32 GetRotation() const { return mRotation; }
	void SetRotation(f32 rot) { mRotation = rot; }

	Game &GetGame() { return *mGame; }

private:
	LogPtr log = spdlog::get("ENT");

protected:
	Game *mGame;

	State mState;
	Category mCategory;

	raylib::Vector2 mPosition;
	raylib::Vector2 mVelocity;
	f32 mMaxMoveSpeed; // In Einheiten/s
	f32 mAcceleration; // In Einheiten/s^2

	f32 mScale;
	f32 mRotation;

	raylib::Rectangle mCollisionRect;
	raylib::Vector2 mCollisionRectOffset;

	void SwitchToAnimation(Animations::ID anim);
	Animation mCurrentAnimation;
};