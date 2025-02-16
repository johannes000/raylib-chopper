#include "PlayerHeli.hpp"
#include <format>

namespace {
constexpr f32 HeliHeight = 10.f;
constexpr f32 HeliWidth = 20.f;
}; // namespace

PlayerHeli::PlayerHeli(Game *game)
	: Entity(game),
	  mDrawrect(0),
	  mRoationPoint(0) {
	mDrawrect.SetHeight(HeliHeight);
	mDrawrect.SetWidth(HeliWidth);
	mMaxMoveSpeed = 50.f;
	mAcceleration = 1.5f;

	mRoationPoint.y = HeliHeight / 2.f;
	mRoationPoint.x = HeliWidth * 1.f / 3.f;

	mHasAcceleration = true;
}

PlayerHeli::~PlayerHeli() {
}

void PlayerHeli::UpdateEntity() {
	mDrawrect.SetPosition(GetPosition());
}

void PlayerHeli::Draw() const {
	mDrawrect.Draw(RED);
	DrawText(std::format("{:.1f}", mVelocity.Length()).c_str(), mPosition.x, mPosition.y, 1, WHITE);
}

void PlayerHeli::ProcessInput() {
	raylib::Vector2 moveDir{};
	if (IsKeyDown(KEY_W))
		moveDir.y = -1;
	if (IsKeyDown(KEY_S))
		moveDir.y = 1;
	if (IsKeyDown(KEY_A))
		moveDir.x = -1;
	if (IsKeyDown(KEY_D))
		moveDir.x = 1;
	if (moveDir.Length() > 0) {
		moveDir = moveDir.Normalize();
	}
	// Normalisiere die Bewegungsrichtung
	if (moveDir.Length() > 0) {
		moveDir = moveDir.Normalize();
	}

	raylib::Vector2 targetVelocity = moveDir * mMaxMoveSpeed;

	mVelocity = mVelocity + (targetVelocity - mVelocity) * mAcceleration * GetFrameTime();
	// if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
	// 	FireProjectile();
	// if (IsMouseButtonPressed(MOUSE_BUTTON_RIGHT))
	// 	FireRocket();
}
