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
	PlayerIdle_1,
	PlayerIdle_2,
	PlayerIdle_3,
	PlayerIdle_4,
	PlayerIdle_5,
	PlayerIdle_6,
	PlayerRun_1,
	PlayerRun_2,
	PlayerRun_3,
	PlayerRun_4,
	PlayerRun_5,
	PlayerRun_6,
	PlayerRun_7,
	PlayerRun_8,
	PlayerAttack1_1,
	PlayerAttack1_2,
	PlayerAttack1_3,
	PlayerAttack1_4,
	PlayerAttack1_5,
	PlayerAttack1_6,
	PlayerAttack2_1,
	PlayerAttack2_2,
	PlayerAttack2_3,
	PlayerAttack2_4,
	PlayerAttack2_5,
	PlayerAttack2_6,
	PlayerAttackBow_1,
	PlayerAttackBow_2,
	PlayerAttackBow_3,
	PlayerAttackBow_4,
	PlayerAttackBow_5,
	PlayerAttackBow_6,
	PlayerAttackBow_7,
	PlayerAttackBow_8,
	PlayerAttackBow_9,
	PlayerHit_1,
	PlayerHit_2,
	PlayerHit_3,
	PlayerHit_4,
	PlayedDeath_1,
	PlayedDeath_2,
	PlayedDeath_3,
	PlayedDeath_4,

	TextureCount
};
};

namespace Animations {
enum class ID {
	NONE,
	PlayerIdle,
	PlayerRun,
	PlayerAttack1,
	PlayerAttack2,
	PlayerAttackBow,
	PlayerHit,
	PlayedDeath,

	AnimationCount
};
}