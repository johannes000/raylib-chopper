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
	  mHorizontalRotationState(HorizontalRotationState::Middle),
	  mMoveDirection(MoveDirection::Stopped),
	  mLastMoveDirection(MoveDirection::Stopped) {
	mMaxMoveSpeed = 50.f;
	mAcceleration = 1.5f;
}

PlayerHeli::~PlayerHeli() {
}

void PlayerHeli::UpdateEntity() {
	UpdateHorizontalRotationState();
}

void PlayerHeli::Draw() const {
	auto [posX, posY] = GetPosition();
	raylib::Rectangle rect{posX, posY, HeliFrontWidth, HeliHeight};

	f32 rot = MaxRotation * mVelocity.x / mMaxMoveSpeed;
	// rot = mVelocity.x < 0 ? -rot : rot;

	Textures::ID texture = Textures::HeliSide;
	if (mHorizontalRotationState == HorizontalRotationState::Middle)
		texture = Textures::HeliFront;

	Sprite.Draw(texture, mPosition, rot);

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
	// if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
	// 	FireProjectile();
	// if (IsMouseButtonPressed(MOUSE_BUTTON_RIGHT))
	// 	FireRocket();
}

void PlayerHeli::UpdateHorizontalRotationState() {
	if (mMoveDirection == MoveDirection::Stopped)
		return;

	if (mMoveDirection != mLastMoveDirection) {
		mHorizontalRotationTimer = 0.f;
		return;
	}

	if (mLastMoveDirection == mMoveDirection) {
		mHorizontalRotationTimer += GetFrameTime();
	}

	if (mHorizontalRotationTimer > TimeToHorizontalTransition) {
		mHorizontalRotationTimer = 0.f;

		i32 state = static_cast<i32>(mHorizontalRotationState);
		state = mMoveDirection == MoveDirection::Left ? state - 1 : state + 1;
		state = std::clamp(state, static_cast<i32>(HorizontalRotationState::Left), static_cast<i32>(HorizontalRotationState::Right));

		mHorizontalRotationState = static_cast<HorizontalRotationState>(state);
	}
}

raylib::Vector2 PlayerHeli::GetRotationPoint() const {
	using enum HorizontalRotationState;
	switch (mHorizontalRotationState) {
		case Left: {
			return raylib::Vector2(RoationPointLeft, RotationPointHeight);
		}
		case LeftMiddle: {
			return raylib::Vector2(RotationPointTransitionLeft, RotationPointHeight);
		}
		case Middle: {
			return raylib::Vector2(RotationPointFront, RotationPointHeight);
		}
		case RightMiddle: {
			return raylib::Vector2(RotationPointTransitionRight, RotationPointHeight);
		}
		case Right: {
			return raylib::Vector2(RoationPointRight, RotationPointHeight);
		}
		default: {
			return raylib::Vector2(RotationPointFront, RotationPointHeight);
		}
	}
}
