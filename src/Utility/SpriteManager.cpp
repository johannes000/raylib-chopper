#include "SpriteManager.hpp"
#include <cassert>

SpriteManager *SpriteManager::Instance = nullptr;

SpriteManager::~SpriteManager() {
}

SpriteManager::SpriteManager(const std::string &texturePath) {
	mTexture.Load(texturePath);
}

void SpriteManager::Init(const std::string &texturePath) {
	assert(!Instance);
	Instance = new SpriteManager(texturePath);
	assert(Instance);

	Sprite.AddTextureRect(Textures::HeliSide, raylib::Rectangle(112, 32, 32, 16));
	Sprite.AddTextureRect(Textures::HeliFront, raylib::Rectangle(144, 32, 16, 16));
	Sprite.AddTextureRect(Textures::HeliRotor, raylib::Rectangle(112, 48, 47, 1));
}

void SpriteManager::Shutdown() {
}

SpriteManager &SpriteManager::GetInstance() {
	assert(Instance);
	return *Instance;
}

void SpriteManager::AddTextureRect(Textures::ID id, raylib::Rectangle rect) {
	mTextureRects[id] = rect;
}

std::optional<Rectangle> FindTextureRect(const std::unordered_map<Textures::ID, raylib::Rectangle> &textureRects, Textures::ID id) {
	auto it = textureRects.find(id);
	if (it != textureRects.end()) {
		return it->second;
	} else {
		LOG.error("{} Kann die Textur mit der ID {} nicht finden.", __FUNCTION__, (i32)id);
		return std::nullopt;
	}
}

raylib::Rectangle SpriteManager::GetTextureRect(Textures::ID id) {
	auto rect = FindTextureRect(mTextureRects, id);
	if (!rect.has_value()) {
		return raylib::Rectangle{};
	}
	return rect.value();
}

void SpriteManager::Draw(Textures::ID id, raylib::Vector2 position, f32 rotation, bool hflip, bool vflip, f32 scale, Color tint) const {
	auto rect = FindTextureRect(mTextureRects, id);
	if (!rect.has_value()) {
		return;
	}
	raylib::Rectangle sourceRect = rect.value();

	raylib::Rectangle destRect = {
		position.x,
		position.y,
		rect->width * scale,
		rect->height * scale};

	if (hflip) {
		// sourceRect.x += sourceRect.width;
		sourceRect.width *= -1;
	}
	if (vflip)
		sourceRect.height *= -1;

	mTexture.Draw(sourceRect,
				  destRect,
				  {destRect.width / 2, destRect.height / 2}, // Origin
				  rotation,
				  tint);
}

void SpriteManager::DrawSegment(raylib::Vector2 position, raylib::Rectangle sourceRect,
								raylib::Vector2 origin, f32 rotation,
								bool hflip, bool vflip, f32 scale,
								Color tint) const {
	raylib::Rectangle destRect = {
		position.x,
		position.y,
		sourceRect.width * scale,
		sourceRect.height * scale};

	if (hflip) {
		// sourceRect.x += sourceRect.width;
		sourceRect.width *= -1;
	}
	if (vflip)
		sourceRect.height *= -1;

	mTexture.Draw(sourceRect,
				  destRect,
				  origin,
				  rotation,
				  tint);
}
