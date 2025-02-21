#pragma once

#include "Utility\Includes.hpp"
#include "Entity.hpp"

class PlayerHeli : public Entity {
private:
	enum struct HorizontalRotationState {
		Left,
		LeftMiddle,
		Middle,
		RightMiddle,
		Right
	};

	enum struct MoveDirection {
		Left,
		Right,
		Stopped
	};

public:
	PlayerHeli(Game *game);
	~PlayerHeli();

	void UpdateEntity() override; // Entity Spezifisches update
	void Draw() const override;
	void ProcessInput() override;

	void UpdateHorizontalRotationState();

	raylib::Vector2 GetRotationPointWorldPosition() const { return mPosition + GetRotationPoint(); };
	raylib::Vector2 GetRotationPoint() const;

	f32 mHorizontalRotationTimer;
	HorizontalRotationState mHorizontalRotationState;

	MoveDirection mMoveDirection;
	MoveDirection mLastMoveDirection;

private:
};