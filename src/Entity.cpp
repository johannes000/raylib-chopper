#include "Entity.hpp"

Entity::~Entity() {
}

void Entity::Update() {
	mPosition += mVelocity * GetFrameTime();
	UpdateCollisionData();
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

bool Entity::CheckGroundCollision(raylib::Rectangle) {
	return false;
}

bool Entity::CheckMapBoundryCollision(raylib::Rectangle) {
	return false;
}

void Entity::OnGroundCollision(raylib::Rectangle) {
}

void Entity::OnMapBoundryCollision(raylib::Rectangle) {
}

CollisionData Entity::GetCurrentCollisionData() const {
	return CollisionData();
}

void Entity::UpdateCollisionData() {
	mCollisionRect.SetPosition(mPosition + mCollisionRectOffset);
}

std::array<raylib::Vector2, 4> Entity::GetTransformedCollisionRect() const {
	std::array<raylib::Vector2, 4> corners = {
		raylib::Vector2{mCollisionRect.x, mCollisionRect.y},
		raylib::Vector2{mCollisionRect.x + mCollisionRect.width, mCollisionRect.y},
		raylib::Vector2{mCollisionRect.x + mCollisionRect.width, mCollisionRect.y + mCollisionRect.height},
		raylib::Vector2{mCollisionRect.x, mCollisionRect.y + mCollisionRect.height}};

	const f32 sinRotation = sinf(mRotation * DEG2RAD);
	const f32 cosRotation = cosf(mRotation * DEG2RAD);

	for (auto &corner : corners) {
		// Rotieren

		corner.x = corner.x * cosRotation - corner.y * sinRotation;

		corner.y = corner.x * sinRotation + corner.y * cosRotation;
	}
	return corners;
}

Entity::Entity(Game *game) : mGame(game),
							 mState(State::Active),
							 mPosition(raylib::Vector2().Zero()),
							 mVelocity(raylib::Vector2().Zero()),
							 mMaxMoveSpeed(0.f),
							 mScale(1.f),
							 mRotation(0.f) {
}
