#include "Entity.hpp"

Entity::~Entity() {
}

void Entity::Update() {

	mPosition += mVelocity * GetFrameTime();
	if (mState == State::Active) {
		UpdateEntity();
	}
}

void Entity::UpdateEntity() {
}

void Entity::Draw() const {
}

void Entity::ProcessInput() {
}

Entity::Entity(Game *game) : mGame(game),
							 mState(State::Active),
							 mPosition(raylib::Vector2().Zero()),
							 mVelocity(raylib::Vector2().Zero()),
							 mMaxMoveSpeed(0.f),
							 mScale(1.f),
							 mRotation(0.f) {
}
