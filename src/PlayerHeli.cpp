#include "PlayerHeli.hpp"

PlayerHeli::PlayerHeli(Game *game) : Entity(game) {
	mDrawrect = raylib::Rectangle(0.f, 0.f, 200.f, 100.f);
}

PlayerHeli::~PlayerHeli() {
}

void PlayerHeli::UpdateEntity() {
}

void PlayerHeli::Draw() const {
	mDrawrect.Draw(GetPosition(), GetRotation(), RED);
}

void PlayerHeli::ProcessInput() {
}
