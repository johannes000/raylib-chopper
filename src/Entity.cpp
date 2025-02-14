#include "Entity.hpp"

Entity::~Entity() {
}

void Entity::Update() {
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
							 mScale(1.f),
							 mRotation(0.f) {
}
