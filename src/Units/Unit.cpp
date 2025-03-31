#include "Unit.hpp"

Unit::Unit(Game *game, Unit::Type type)
	: Entity(game),
	  mUnitType(type) {
	using enum Type;
	switch (mUnitType) {
		case Soldier: {
			SwitchToAnimation(Animations::SoldierIdle);
		} break;
		case Orc: {
			SwitchToAnimation(Animations::OrcIdle);
		} break;
		default: {
			SwitchToAnimation(Animations::SoldierIdle);
		} break;
	}
	mCurrentAnimation.Play();
}

void Unit::UpdateEntity() {
}

void Unit::Draw() const {
	auto sprite = mCurrentAnimation.GetCurrentFrame();
	SpriteM.Draw(sprite, mPosition, 0.f);
}

void Unit::ProcessInput() {
}

bool Unit::CheckGroundCollision(raylib::Rectangle groundRect) {
	return false;
}

bool Unit::CheckMapBoundryCollision(raylib::Rectangle bounds) {
	return false;
}

void Unit::OnGroundCollision(raylib::Rectangle groundRect) {
}

void Unit::OnMapBoundryCollision(raylib::Rectangle bounds) {
}

CollisionData Unit::GetCurrentCollisionData() const {
}

void Unit::UpdateCollisionData() {
}
