#pragma once

#include "Utility\Includes.hpp"
#include "Entity.hpp"

class PlayerHeli : public Entity {
private:
	enum struct FaceDirection {
		Left,
		Middle,
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

	raylib::Vector2 GetRotationPointWorldPosition() const { return mPosition + GetRotationPoint(); };
	raylib::Vector2 GetRotationPoint() const;

	f32 mHorizontalRotationTimer;
	FaceDirection mFaceDirection;

	MoveDirection mMoveDirection;
	MoveDirection mLastMoveDirection;

private:
	raylib::Rectangle GetCurrentTextureRect() const;
};