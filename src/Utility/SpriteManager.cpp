#include "SpriteManager.hpp"

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

	SpriteM.AddSprite(Sprites::PlayerIdle_1, {raylib::Rectangle(0, 0, 15, 19), raylib::Vector2(0.f, 0.f)});
	SpriteM.AddSprite(Sprites::PlayerIdle_2, {raylib::Rectangle(16, 0, 15, 19), raylib::Vector2(0.f, 0.f)});
	SpriteM.AddSprite(Sprites::PlayerIdle_3, {raylib::Rectangle(32, 0, 15, 19), raylib::Vector2(0.f, 0.f)});
	SpriteM.AddSprite(Sprites::PlayerIdle_4, {raylib::Rectangle(48, 0, 15, 19), raylib::Vector2(0.f, 0.f)});
	SpriteM.AddSprite(Sprites::PlayerIdle_5, {raylib::Rectangle(64, 0, 15, 19), raylib::Vector2(0.f, 0.f)});
	SpriteM.AddSprite(Sprites::PlayerIdle_6, {raylib::Rectangle(80, 0, 15, 19), raylib::Vector2(0.f, 0.f)});
}

void SpriteManager::Shutdown() {
}

SpriteManager &SpriteManager::GetInstance() {
	assert(Instance);
	return *Instance;
}

void SpriteManager::AddSprite(Sprites::ID id, Sprite sprite) {
	mTextures[id] = sprite;
}

std::optional<Sprite> FindTextureRect(const std::unordered_map<Sprites::ID, Sprite> &textureRects, Sprites::ID id) {
	auto log = spdlog::get("SPRM");
	auto it = textureRects.find(id);
	if (it != textureRects.end()) {
		return it->second;
	} else {
		log->error("{} Kann die Textur mit der ID {} nicht finden.", __FUNCTION__, (i32)id);
		return std::nullopt;
	}
}

Sprite SpriteManager::GetSprite(Sprites::ID id) {
	auto rect = FindTextureRect(mTextures, id);
	if (!rect.has_value()) {
		return Sprite{};
	}
	return rect.value();
}

void SpriteManager::Draw(Sprites::ID id, raylib::Vector2 position, raylib::Vector2 origin, f32 rotation, bool hflip, bool vflip, f32 scale, Color tint) const {
	auto rect = FindTextureRect(mTextures, id);
	if (!rect.has_value()) {
		return;
	}
	auto sprite = rect.value();
	raylib::Rectangle sourceRect = sprite.drawRect;

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
				  //   {destRect.width / 2, destRect.height / 2}, // Origin
				  rotation,
				  tint);
}

void SpriteManager::Draw(Sprites::ID id, raylib::Vector2 position, f32 rotation, bool hflip, bool vflip, f32 scale, Color tint) const {
	auto sprite = FindTextureRect(mTextures, id);
	if (!sprite.has_value()) {
		return;
	}
	Draw(id, position, sprite->origin, rotation, hflip, vflip, scale, tint);
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
