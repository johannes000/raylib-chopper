#pragma once

#include "Entity.hpp"
#include "Utility\AnimationManager.hpp"
#include "Utility\Includes.hpp"

class Unit : public Entity {
public:
	enum struct Type {
		Soldier,
		Orc
	};
	enum struct State {
		Moving,
		Attacking,
		Idle
	};

public:
	Unit(Game *game, Unit::Type type);

	void UpdateEntity() override; // Entity Spezifisches update
	void Draw() const override;
	void ProcessInput() override;

	bool CheckGroundCollision(raylib::Rectangle groundRect) override; // return true bei Kollision
	bool CheckMapBoundryCollision(raylib::Rectangle bounds) override; // return true bei Kollision

	void OnGroundCollision(raylib::Rectangle groundRect) override;
	void OnMapBoundryCollision(raylib::Rectangle bounds) override;

	CollisionData GetCurrentCollisionData() const override;
	void UpdateCollisionData() override;

private:
	Type mUnitType;
	State mUnitState;
	bool mIsAttacking;

	void UpdateOrcStatemachiene();
	void UpdateSoldierStatemachiene();
};