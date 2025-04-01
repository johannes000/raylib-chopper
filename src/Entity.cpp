#include "Entity.hpp"

Entity::~Entity() {
}

void Entity::Update() {
	mPosition += mVelocity * GetFrameTime();
	UpdateCollisionData();

	mCurrentAnimation.Update(GetFrameTime() * mAnimationSpeedFactor);
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
	raylib::Vector2 center = {
		mCollisionRect.x + mCollisionRect.width / 2.0f,
		mCollisionRect.y + mCollisionRect.height / 2.0f};

	std::array<raylib::Vector2, 4> corners = {
		raylib::Vector2{mCollisionRect.x - center.x, mCollisionRect.y - center.y},
		raylib::Vector2{mCollisionRect.x + mCollisionRect.width - center.x, mCollisionRect.y - center.y},
		raylib::Vector2{mCollisionRect.x + mCollisionRect.width - center.x, mCollisionRect.y + mCollisionRect.height - center.y},
		raylib::Vector2{mCollisionRect.x - center.x, mCollisionRect.y + mCollisionRect.height - center.y}};

	if (mRotation != 0.f) {
		const f32 sinRotation = sinf(mRotation * DEG2RAD);
		const f32 cosRotation = cosf(mRotation * DEG2RAD);

		for (auto &corner : corners) {
			f32 x = corner.x * cosRotation - corner.y * sinRotation;
			f32 y = corner.x * sinRotation + corner.y * cosRotation;
			corner.x = x + center.x;
			corner.y = y + center.y;
		}
	}
	return corners;
}

void Entity::SwitchToAnimation(Animations::ID anim) {
	if (mCurrentAnimation.ID() != anim) {
		mCurrentAnimation.Reset();
		mCurrentAnimation = AniM.GetAnimation(anim);
		mCurrentAnimation.Play();
	}
}

Entity::Entity(Game *game) : mGame(game),
							 mState(State::Active),
							 mPosition(raylib::Vector2().Zero()),
							 mVelocity(raylib::Vector2().Zero()),
							 mMaxMoveSpeed(0.f),
							 mScale(1.f),
							 mRotation(0.f),
							 mHFlipped(false),
							 mAnimationSpeedFactor(1.f) {
}
