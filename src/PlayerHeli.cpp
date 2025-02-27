#include "PlayerHeli.hpp"
#include <format>

namespace {
constexpr f32 HeliHeight = 10.f;
constexpr f32 HeliSideWidth = 20.f;
constexpr f32 HeliTransitionWidth = 15.f;
constexpr f32 HeliFrontWidth = 10.f;

constexpr f32 RotationPointHeight = HeliHeight / 2.f;
constexpr f32 RoationPointRight = HeliSideWidth * 1.f / 3.f;
constexpr f32 RoationPointLeft = HeliSideWidth * 2.f / 3.f;
constexpr f32 RotationPointTransitionRight = HeliTransitionWidth * 1.f / 3.f;
constexpr f32 RotationPointTransitionLeft = HeliTransitionWidth * 2.f / 3.f;
constexpr f32 RotationPointFront = HeliFrontWidth / 2.f;

constexpr f32 MaxRotation = 45.f;

constexpr f32 TimeToHorizontalTransition = .5f; // Wie Lange der Heli braucht um von einem HorizontalRotationState zum nächsten zu transitionen in Sekunden

}; // namespace

PlayerHeli::PlayerHeli(Game *game)
	: Entity(game),
	  mHorizontalRotationTimer(0.f),
	  mFaceDirection(FaceDirection::Middle),
	  mMoveDirection(MoveDirection::Stopped),
	  mLastMoveDirection(MoveDirection::Stopped) {
	mMaxMoveSpeed = 50.f;
	mAcceleration = 1.5f;
}

PlayerHeli::~PlayerHeli() {
}

void PlayerHeli::UpdateEntity() {
}

void PlayerHeli::Draw() const {
	auto [posX, posY] = GetPosition();
	raylib::Rectangle rect{posX, posY, HeliFrontWidth, HeliHeight};

	f32 rot = MaxRotation * mVelocity.x / mMaxMoveSpeed;
	// rot = mVelocity.x < 0 ? -rot : rot;

	Textures::ID texture = Textures::HeliSide;
	if (mFaceDirection == FaceDirection::Middle)
		texture = Textures::HeliFront;

	bool hflip = mFaceDirection == FaceDirection::Left;
	Sprite.Draw(texture, mPosition, rot, hflip);

	// mDrawrect.Draw(GetRotationPoint(), rot, YELLOW);
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

raylib::Vector2 PlayerHeli::GetRotationPoint() const {
	using enum FaceDirection;
	return raylib::Vector2(RotationPointFront, RotationPointHeight);
}
