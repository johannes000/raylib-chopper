#pragma once
#include "Includes.hpp"

class SpriteManager {
public:
	SpriteManager(SpriteManager const &) = delete;
	void operator=(SpriteManager const &) = delete;

	static void Init(const std::string &texturePath);
	static void Shutdown();

	static SpriteManager &GetInstance();

	void AddTextureRect(Textures::ID id, raylib::Rectangle rect);
	raylib::Rectangle GetTextureRect(Textures::ID id);

	void Draw(Textures::ID id, raylib::Vector2 position, f32 rotation, bool hflip = false, bool vflip = false, f32 scale = 1.f, Color tint = WHITE) const;
	void Draw(Textures::ID id, raylib::Vector2 position, raylib::Vector2 origin, f32 rotation, bool hflip = false, bool vflip = false, f32 scale = 1.f, Color tint = WHITE) const;
	void DrawSegment(raylib::Vector2 position, raylib::Rectangle sourceRect, raylib::Vector2 origin, f32 rotation = 0.f, bool hflip = false, bool vflip = false, f32 scale = 1.f, Color tint = WHITE) const;

private:
	SpriteManager(const std::string &texturePath);
	~SpriteManager();

	raylib::Texture2D mTexture;
	std::unordered_map<Textures::ID, raylib::Rectangle> mTextureRects;

	static SpriteManager *Instance;
};

#define Sprite SpriteManager::GetInstance()