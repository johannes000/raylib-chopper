#include "Unit.hpp"
#include "Game.hpp"

namespace {
struct UnitSpecs {
	Animations::ID defaultAnimation;
	f32 maxMoveSpeed{0};
};

constexpr UnitSpecs GetUnitSpecs(Unit::Type type) {
	UnitSpecs us;
	using enum Unit::Type;
	switch (type) {
		case Soldier: {
			us.defaultAnimation = Animations::SoldierIdle;
			us.maxMoveSpeed = 20.f;
		} break;
		case Orc: {
			us.defaultAnimation = Animations::OrcIdle;
			us.maxMoveSpeed = 20.f;
		} break;
	}
	return us;
};
}; // namespace

Unit::Unit(Game *game, Unit::Type type)
	: Entity(game),
	  mUnitType(type),
	  mUnitState(State::Idle),
	  mIsAttacking(false) {
	auto us = GetUnitSpecs(type);

	mMaxMoveSpeed = us.maxMoveSpeed;
	SwitchToAnimation(us.defaultAnimation);
}

void Unit::UpdateEntity() {
	auto ground = mGame->GetGroundRect();
	mPosition.y = ground.y + 10;
	using enum Type;
	switch (mUnitType) {
		case Soldier: {
			UpdateSoldierStatemachiene();
		} break;
		case Orc: {
			UpdateOrcStatemachiene();
		} break;
	}
}

void Unit::Draw() const {
	auto spriteID = mCurrentAnimation.GetCurrentFrameID();

	SpriteM.Draw(spriteID, mPosition, 0.f, mHFlipped);
	DrawCircle(mPosition.x, mPosition.y, 1.f, RED);
}

void Unit::ProcessInput() {
	mVelocity.x = 0;
	if (mUnitType == Type::Soldier) {
		if (IsKeyDown(KEY_RIGHT)) {
			mHFlipped = false;
			mVelocity.x = mMaxMoveSpeed;
		}
		if (IsKeyDown(KEY_LEFT)) {
			mHFlipped = true;
			mVelocity.x = -mMaxMoveSpeed;
		}
		if (IsKeyDown(KEY_A)) {
			mIsAttacking = true;
		}
	}
}

bool Unit::CheckGroundCollision(raylib::Rectangle /* groundRect */) {
	return false;
}

bool Unit::CheckMapBoundryCollision(raylib::Rectangle /* bounds */) {
	return false;
}

void Unit::OnGroundCollision(raylib::Rectangle /* groundRect */) {
}

void Unit::OnMapBoundryCollision(raylib::Rectangle /* bounds */) {
}

CollisionData Unit::GetCurrentCollisionData() const {
	return CollisionData{};
}

void Unit::UpdateCollisionData() {
}

void Unit::UpdateOrcStatemachiene() {
}

void Unit::UpdateSoldierStatemachiene() {
	using enum State;
	switch (mUnitState) {
		case Idle: {
			SwitchToAnimation(Animations::SoldierIdle);
			if (mIsAttacking) {
				mUnitState = Attacking;
			} else if (mVelocity.Length() > 0.f) {
				mUnitState = Moving;
			}
		} break;
		case Moving: {
			SwitchToAnimation(Animations::SoldierRun);
			if (mIsAttacking) {
				mUnitState = Attacking;
			} else if (mVelocity.Length() == 0.f) {
				mUnitState = Idle;
			}
		} break;
		case Attacking: {
			SwitchToAnimation(Animations::SoldierAttack1);
			mVelocity.x = 0.f;
			if (mCurrentAnimation.IsComplete()) {
				mIsAttacking = false;
				if (mVelocity.Length() == 0.f) {
					mUnitState = Idle;
				} else {
					mUnitState = Moving;
				}
			}
		} break;
	}
}
