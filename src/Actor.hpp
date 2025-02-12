#pragma once

#include "Utility\Includes.hpp"

class Component;
class Game;

class Actor {
public:
	enum struct State {
		Active,
		Paused,
		Dead
	};

	typedef std::shared_ptr<Actor> Ptr;
	typedef std::unique_ptr<Actor> UPtr;

	Actor(std::shared_ptr<Game> game);
	virtual ~Actor();

	void Update();
	void UpdateComponents();
	virtual void UpdateActor(); // Actor spezifische Updates

	State GetState() const { return mState; }
	void SetState(State state) { mState = state; }

	const raylib::Vector2 GetPosition() const { return mPosition; }
	void SetPosition(raylib::Vector2 pos) { mPosition = pos; }
	void SetPosition(f32 x, f32 y) { mPosition = raylib::Vector2{x, y}; }

	f32 GetScale() const { return mScale; }
	void SetScale(f32 scale) { mScale = scale; }

	f32 GetRotation() const { return mRotation; }
	void SetRotation(f32 rot) { mRotation = rot; }

	Component *AddComponent(std::unique_ptr<Component> component);
	void RemoveComponent(Component *component);

private:
	State mState;

	raylib::Vector2 mPosition;
	f32 mScale;
	f32 mRotation;

	std::vector<std::unique_ptr<Component>> mComponents;
	std::shared_ptr<Game> mGame;
};