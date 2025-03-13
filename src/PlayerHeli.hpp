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

	bool CheckGroundCollision(raylib::Rectangle groundRect) override; // return true bei Kollision
	bool CheckMapBoundryCollision(raylib::Rectangle bounds) override; // return true bei Kollision

	void OnGroundCollision(raylib::Rectangle groundRect) override;
	void OnMapBoundryCollision(raylib::Rectangle bounds) override;

	raylib::Vector2 GetRotationPointWorldPosition() const { return mPosition + GetRotationPoint(); };
	raylib::Vector2 GetRotationPoint() const;

	inline CollisionData GetCurrentCollisionData() const override;
	void UpdateCollisionData() override;

	f32 mHorizontalRotationTimer;
	FaceDirection mFaceDirection;

	MoveDirection mMoveDirection;
	MoveDirection mLastMoveDirection;

private:
	raylib::Rectangle GetCurrentTextureRect() const;

	bool mRotorFlip;
	f32 mRotorFliptime;
};