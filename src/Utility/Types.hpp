#pragma once

#include <cstdint>

typedef uint8_t u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;

typedef int8_t i8;
typedef int16_t i16;
typedef int32_t i32;
typedef int64_t i64;

typedef float f32;
typedef double f64;

#define global static

constexpr i32 GAME_SCREEN_WIDTH = 1200;
constexpr i32 GAME_SCREEN_HEIGHT = GAME_SCREEN_WIDTH * 1080 / 1920;

constexpr i32 MAP_TILE_SIZE = 16;
constexpr f32 MAP_TILE_SIZE_F32 = (f32)MAP_TILE_SIZE;
constexpr i32 UNIT_TILE_SIZE = 16;
constexpr f32 UNIT_TILE_SIZE_F32 = (f32)UNIT_TILE_SIZE;

namespace TextureAtlas {
enum ID {
	NONE,

	Sprites01,

	AtlasCount
};
};

namespace Sprites {
enum ID {
	NONE,
	// Soldier
	SoldierIdle_1,
	SoldierIdle_2,
	SoldierIdle_3,
	SoldierIdle_4,
	SoldierIdle_5,
	SoldierIdle_6,
	SoldierRun_1,
	SoldierRun_2,
	SoldierRun_3,
	SoldierRun_4,
	SoldierRun_5,
	SoldierRun_6,
	SoldierRun_7,
	SoldierRun_8,
	SoldierAttack1_1,
	SoldierAttack1_2,
	SoldierAttack1_3,
	SoldierAttack1_4,
	SoldierAttack1_5,
	SoldierAttack1_6,
	SoldierAttack2_1,
	SoldierAttack2_2,
	SoldierAttack2_3,
	SoldierAttack2_4,
	SoldierAttack2_5,
	SoldierAttack2_6,
	SoldierAttackBow_1,
	SoldierAttackBow_2,
	SoldierAttackBow_3,
	SoldierAttackBow_4,
	SoldierAttackBow_5,
	SoldierAttackBow_6,
	SoldierAttackBow_7,
	SoldierAttackBow_8,
	SoldierAttackBow_9,
	SoldierHit_1,
	SoldierHit_2,
	SoldierHit_3,
	SoldierHit_4,
	SoldierDeath_1,
	SoldierDeath_2,
	SoldierDeath_3,
	SoldierDeath_4,
	// Orc
	OrcIdle_1,
	OrcIdle_2,
	OrcIdle_3,
	OrcIdle_4,
	OrcIdle_5,
	OrcIdle_6,
	OrcRun_1,
	OrcRun_2,
	OrcRun_3,
	OrcRun_4,
	OrcRun_5,
	OrcRun_6,
	OrcRun_7,
	OrcRun_8,
	OrcAttack1_1,
	OrcAttack1_2,
	OrcAttack1_3,
	OrcAttack1_4,
	OrcAttack1_5,
	OrcAttack1_6,
	OrcAttack2_1,
	OrcAttack2_2,
	OrcAttack2_3,
	OrcAttack2_4,
	OrcAttack2_5,
	OrcAttack2_6,
	OrcAttackBow_1,
	OrcAttackBow_2,
	OrcAttackBow_3,
	OrcAttackBow_4,
	OrcAttackBow_5,
	OrcAttackBow_6,
	OrcAttackBow_7,
	OrcAttackBow_8,
	OrcAttackBow_9,
	OrcHit_1,
	OrcHit_2,
	OrcHit_3,
	OrcHit_4,
	OrcDeath_1,
	OrcDeath_2,
	OrcDeath_3,
	OrcDeath_4,
	TextureCount
};
};

namespace Animations {
enum ID {
	NONE,
	// Soldier
	SoldierIdle,
	SoldierRun,
	SoldierAttack1,
	SoldierAttack2,
	SoldierAttackBow,
	SoldierHit,
	SoldierDeath,
	// Orc
	OrcIdle,
	OrcRun,
	OrcAttack1,
	OrcAttack2,
	OrcAttackBow,
	OrcHit,
	OrcDeath,

	AnimationCount
};
}