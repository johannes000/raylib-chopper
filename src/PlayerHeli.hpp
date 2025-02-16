#pragma once

#include "Utility\Includes.hpp"
#include "Entity.hpp"

class PlayerHeli : public Entity {
public:
	PlayerHeli(Game *game);
	~PlayerHeli();

	void UpdateEntity() override; // Entity Spezifisches update
	void Draw() const override;
	void ProcessInput() override;

	raylib::Vector2 GetRotationPointWorldPosition() const { return mPosition + mRoationPoint; };

private:
	raylib::Rectangle mDrawrect;
	raylib::Vector2 mRoationPoint;
};