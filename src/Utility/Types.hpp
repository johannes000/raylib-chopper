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

namespace Textures {
enum ID {
	NONE,

	HeliSide,
	HeliFront,

	TextureCount,
};
};