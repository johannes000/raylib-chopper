#pragma once
#include "Includes.hpp"

struct Sprite {
	raylib::Rectangle drawRect{};
	raylib::Vector2 origin{};
	raylib::Rectangle hurtbox{}; // offsetX,offsetY,....
};

class SpriteManager {
public:
	SpriteManager(SpriteManager const &) = delete;
	void operator=(SpriteManager const &) = delete;

	static void Init(const std::string &texturePath);
	static void Shutdown();

	static SpriteManager &GetInstance();

	void AddSprite(Sprites::ID id, Sprite sprite);
	Sprite GetSprite(Sprites::ID id);

	void Draw(Sprites::ID id, raylib::Vector2 position, f32 rotation = 0.f, bool hflip = false, bool vflip = false, f32 scale = 1.f, Color tint = WHITE) const;
	void Draw(Sprites::ID id, raylib::Vector2 position, raylib::Vector2 origin, f32 rotation = 0.f, bool hflip = false, bool vflip = false, f32 scale = 1.f, Color tint = WHITE) const;
	void DrawSegment(raylib::Vector2 position, raylib::Rectangle sourceRect, raylib::Vector2 origin, f32 rotation = 0.f, bool hflip = false, bool vflip = false, f32 scale = 1.f, Color tint = WHITE) const;

private:
	SpriteManager(const std::string &texturePath);
	~SpriteManager();

	raylib::Texture2D mTexture;
	std::unordered_map<Sprites::ID, Sprite> mTextures;
	static SpriteManager *Instance;

	LogPtr mLog = AddLogger("SPR");
};

#define SpriteM SpriteManager::GetInstance()