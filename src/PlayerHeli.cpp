#include "PlayerHeli.hpp"

PlayerHeli::PlayerHeli(Game *game) : Entity(game) {
	mDrawrect.SetHeight(100);
	mDrawrect.SetWidth(200);
	mMaxMoveSpeed = 400.f;
}

PlayerHeli::~PlayerHeli() {
}

void PlayerHeli::UpdateEntity() {
	mDrawrect.SetPosition(GetPosition());
}

void PlayerHeli::Draw() const {
	mDrawrect.Draw(RED);
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
	mVelocity = moveDir.Normalize() * mMaxMoveSpeed;

	// if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
	// 	FireProjectile();
	// if (IsMouseButtonPressed(MOUSE_BUTTON_RIGHT))
	// 	FireRocket();
}
