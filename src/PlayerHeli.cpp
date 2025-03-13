#include "PlayerHeli.hpp"
#include <format>

namespace {
constexpr f32 MaxRotation = 45.f;
constexpr f32 RotorFrq = 2.f; // Wie oft der Rotor pro sekunde flipt

}; // namespace

PlayerHeli::PlayerHeli(Game *game)
	: Entity(game),
	  mHorizontalRotationTimer(0.f),
	  mFaceDirection(FaceDirection::Middle),
	  mMoveDirection(MoveDirection::Stopped),
	  mLastMoveDirection(MoveDirection::Stopped),
	  mRotorFlip(false),
	  mRotorFliptime(1.f / RotorFrq) {
	mMaxMoveSpeed = 50.f;
	mAcceleration = 1.5f;
	mCollisionRect.SetSize(GetCurrentTextureRect().height, GetCurrentTextureRect().height);
}

PlayerHeli::~PlayerHeli() {
}

void PlayerHeli::UpdateEntity() {
	mRotorFliptime += GetFrameTime();
	const f32 rotorFlipTrechholdTime = 1.f / RotorFrq;
	if (mRotorFliptime >= rotorFlipTrechholdTime) {
		mRotorFlip = !mRotorFlip;
		mRotorFliptime -= rotorFlipTrechholdTime;
	}
	mRotation = MaxRotation * mVelocity.x / mMaxMoveSpeed;
}

void PlayerHeli::Draw() const {
	const auto [posX, posY] = GetPosition();
	const auto drawRect = GetCurrentTextureRect();

	Textures::ID texture = Textures::HeliSide;
	if (mFaceDirection == FaceDirection::Middle)
		texture = Textures::HeliFront;

	bool hflip = mFaceDirection == FaceDirection::Left;
	Sprite.Draw(texture, GetRotationPointWorldPosition(), mRotation, hflip, false, 1.f);

	static i32 rotorCount = 0;

	auto [rotX, rotY] = GetRotationPoint();
	auto [rotorPosX, rotorPosY] = GetRotationPointWorldPosition();

	raylib::Vector2 rotorOffset{0, -6.f};
	rotorOffset = rotorOffset.Rotate(mRotation * DEG2RAD);

	Sprite.Draw(Textures::HeliRotor, raylib::Vector2(rotorPosX, rotorPosY) + rotorOffset, mRotation, mRotorFlip, false, 1.f, WHITE);
	auto cd = GetCurrentCollisionData();

	mCollisionRect.DrawLines(GOLD);
	auto corners = GetTransformedCollisionRect();
	for (i32 i = 0; i < 4; i++) {
		i32 next = (i + 1) % 4;
		DrawLine(corners[i].x, corners[i].y, corners[next].x, corners[next].y, GREEN);
	}
	DrawLine(mPosition.x, mPosition.y, corners[0].x, corners[0].y, RED);

	DrawText(std::format("{:.1f}", mVelocity.Length()).c_str(), mPosition.x, mPosition.y, 1, WHITE);
}

void PlayerHeli::ProcessInput() {
	mLastMoveDirection = mMoveDirection;
	mMoveDirection = MoveDirection::Stopped;
	raylib::Vector2 moveDir{0, 0};
	if (IsKeyDown(KEY_W)) {
		moveDir.y = -1;
	}
	if (IsKeyDown(KEY_S)) {
		moveDir.y = 1;
	}
	if (IsKeyDown(KEY_A)) {
		moveDir.x = -1;
		mMoveDirection = MoveDirection::Left;
	}
	if (IsKeyDown(KEY_D)) {
		moveDir.x = 1;
		mMoveDirection = MoveDirection::Right;
	}
	if (moveDir.Length() > 0) {
		moveDir = moveDir.Normalize();
	}
	// Normalisiere die Bewegungsrichtung
	if (moveDir.Length() > 0) {
		moveDir = moveDir.Normalize();
	}

	raylib::Vector2 targetVelocity = moveDir * mMaxMoveSpeed;

	mVelocity = mVelocity + (targetVelocity - mVelocity) * mAcceleration * GetFrameTime();

	// Face Direction
	auto mouseX = GetMousePosition().x;
	f32 drittelRenderWidth = GetRenderWidth() / 3;
	if (mouseX < drittelRenderWidth) {
		mFaceDirection = FaceDirection::Left;
	} else if (mouseX > drittelRenderWidth * 2) {
		mFaceDirection = FaceDirection::Right;
	} else {
		mFaceDirection = FaceDirection::Middle;
	}

	// if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
	// 	FireProjectile();
	// if (IsMouseButtonPressed(MOUSE_BUTTON_RIGHT))
	// 	FireRocket();
}

bool PlayerHeli::CheckGroundCollision(raylib::Rectangle groundRect) {
	return false;
}

bool PlayerHeli::CheckMapBoundryCollision(raylib::Rectangle bounds) {
	auto rect = GetCurrentTextureRect();
	return mPosition.x < bounds.x ||
		   mPosition.y < bounds.y ||
		   mPosition.x + rect.width > bounds.x + bounds.width ||
		   mPosition.y + rect.height > bounds.y + bounds.height;
}

void PlayerHeli::OnGroundCollision(raylib::Rectangle groundRect) {
	mVelocity.y = 0;
}

void PlayerHeli::OnMapBoundryCollision(raylib::Rectangle bounds) {
	auto rect = GetCurrentTextureRect();
	mPosition.x = Clamp(mPosition.x, bounds.x, bounds.x + bounds.width - rect.width);
	mPosition.y = Clamp(mPosition.y, bounds.y, bounds.y + bounds.height - rect.height);
}

raylib::Vector2 PlayerHeli::GetRotationPoint() const {
	return raylib::Vector2(39.f / 2, 4.f);
	using enum FaceDirection;
	switch (mFaceDirection) {

		case Middle: {
			const f32 rotX = 7.5f;
			const f32 rotY = 4.f;
			return raylib::Vector2(rotX, rotY);
		}

		case Left:
		case Right:
		default: {
			const f32 rotX = 22.f;
			const f32 rotY = 4.f;
			return raylib::Vector2(rotX, rotY);
		}
	}
}

CollisionData PlayerHeli::GetCurrentCollisionData() const {
	using enum FaceDirection;
	CollisionData cd{};
	switch (mFaceDirection) {
		case Middle: {
			cd.CollisionRect.SetSize(13.f, 7.f);
			cd.CollisionRectOffset = raylib::Vector2(13.f, 4.f);
		} break;
		case Left: {
			cd.CollisionRect.SetSize(20.f, 7.f);
			cd.CollisionRectOffset = raylib::Vector2(8.f, 4.f);
		} break;
		case Right:
		default: {
			cd.CollisionRect.SetSize(20.f, 7.f);
			cd.CollisionRectOffset = raylib::Vector2(12.f, 4.f);
		} break;
	}
	return cd;
}

void PlayerHeli::UpdateCollisionData() {
	mCollisionRectOffset = GetCurrentCollisionData().CollisionRectOffset;
	// mCollisionRectOffset = mCollisionRectOffset.Rotate(-1 * std::abs(mRotation) * DEG2RAD);

	mCollisionRect = GetCurrentCollisionData().CollisionRect;
	Entity::UpdateCollisionData();
}

raylib::Rectangle PlayerHeli::GetCurrentTextureRect() const {
	using enum FaceDirection;
	switch (mFaceDirection) {
		case Middle: {
			return Sprite.GetTextureRect(Textures::HeliFront);
		}
		case Left:
		case Right:
		default: {
			return Sprite.GetTextureRect(Textures::HeliSide);
		}
	}
}
