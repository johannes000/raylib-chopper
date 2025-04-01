#include "SpriteManager.hpp"

SpriteManager *SpriteManager::Instance = nullptr;

SpriteManager::SpriteManager(const std::string &texturePath) {
	mTexture.Load(texturePath);
}

void SpriteManager::Init(const std::string &texturePath) {
	assert(!Instance);
	Instance = new SpriteManager(texturePath);
	assert(Instance);

	SpriteM.AddSprite(Sprites::SoldierIdle_1, {raylib::Rectangle(0, 0, 15, 19), raylib::Vector2(10.f, 18.f)});
	SpriteM.AddSprite(Sprites::SoldierIdle_2, {raylib::Rectangle(16, 0, 15, 19), raylib::Vector2(10.f, 18.f)});
	SpriteM.AddSprite(Sprites::SoldierIdle_3, {raylib::Rectangle(32, 0, 15, 19), raylib::Vector2(10.f, 18.f)});
	SpriteM.AddSprite(Sprites::SoldierIdle_4, {raylib::Rectangle(48, 0, 15, 19), raylib::Vector2(10.f, 18.f)});
	SpriteM.AddSprite(Sprites::SoldierIdle_5, {raylib::Rectangle(64, 0, 15, 19), raylib::Vector2(10.f, 18.f)});
	SpriteM.AddSprite(Sprites::SoldierIdle_6, {raylib::Rectangle(80, 0, 15, 19), raylib::Vector2(10.f, 18.f)});

	SpriteM.AddSprite(Sprites::SoldierRun_1, {raylib::Rectangle(0, 29, 15, 19), raylib::Vector2(10.f, 19.f)});
	SpriteM.AddSprite(Sprites::SoldierRun_2, {raylib::Rectangle(16, 29, 15, 19), raylib::Vector2(10.f, 19.f)});
	SpriteM.AddSprite(Sprites::SoldierRun_3, {raylib::Rectangle(32, 29, 15, 19), raylib::Vector2(10.f, 19.f)});
	SpriteM.AddSprite(Sprites::SoldierRun_4, {raylib::Rectangle(48, 29, 15, 19), raylib::Vector2(10.f, 19.f)});
	SpriteM.AddSprite(Sprites::SoldierRun_5, {raylib::Rectangle(64, 29, 15, 19), raylib::Vector2(10.f, 19.f)});
	SpriteM.AddSprite(Sprites::SoldierRun_6, {raylib::Rectangle(80, 29, 15, 19), raylib::Vector2(10.f, 19.f)});
	SpriteM.AddSprite(Sprites::SoldierRun_7, {raylib::Rectangle(96, 29, 15, 19), raylib::Vector2(10.f, 19.f)});
	SpriteM.AddSprite(Sprites::SoldierRun_8, {raylib::Rectangle(112, 29, 15, 19), raylib::Vector2(10.f, 19.f)});

	SpriteM.AddSprite(Sprites::SoldierAttack1_1, {raylib::Rectangle(0, 56, 15, 18), raylib::Vector2(10.f, 18.f)});
	SpriteM.AddSprite(Sprites::SoldierAttack1_2, {raylib::Rectangle(16, 49, 19, 24), raylib::Vector2(10.f, 24.f)});
	SpriteM.AddSprite(Sprites::SoldierAttack1_3, {raylib::Rectangle(36, 50, 20, 23), raylib::Vector2(10.f, 23.f)});
	SpriteM.AddSprite(Sprites::SoldierAttack1_4, {raylib::Rectangle(57, 56, 34, 20), raylib::Vector2(13.f, 17.f)});
	SpriteM.AddSprite(Sprites::SoldierAttack1_5, {raylib::Rectangle(92, 56, 34, 20), raylib::Vector2(13.f, 17.f)});
	SpriteM.AddSprite(Sprites::SoldierAttack1_6, {raylib::Rectangle(127, 56, 22, 18), raylib::Vector2(13.f, 17.f)});

	SpriteM.AddSprite(Sprites::OrcIdle_1, {raylib::Rectangle(226, 0, 22, 16), raylib::Vector2(0.f, 0.f)});
	SpriteM.AddSprite(Sprites::OrcIdle_2, {raylib::Rectangle(250, 0, 22, 16), raylib::Vector2(0.f, 0.f)});
	SpriteM.AddSprite(Sprites::OrcIdle_3, {raylib::Rectangle(274, 0, 22, 16), raylib::Vector2(0.f, 0.f)});
	SpriteM.AddSprite(Sprites::OrcIdle_4, {raylib::Rectangle(297, 0, 22, 16), raylib::Vector2(0.f, 0.f)});
	SpriteM.AddSprite(Sprites::OrcIdle_5, {raylib::Rectangle(322, 0, 22, 16), raylib::Vector2(0.f, 0.f)});
	SpriteM.AddSprite(Sprites::OrcIdle_6, {raylib::Rectangle(345, 0, 22, 16), raylib::Vector2(0.f, 0.f)});

	SpriteM.AddSprite(Sprites::OrcRun_1, {raylib::Rectangle(226, 16, 22, 16), raylib::Vector2(0.f, 0.f)});
	SpriteM.AddSprite(Sprites::OrcRun_2, {raylib::Rectangle(250, 16, 22, 16), raylib::Vector2(0.f, 0.f)});
	SpriteM.AddSprite(Sprites::OrcRun_3, {raylib::Rectangle(274, 16, 22, 16), raylib::Vector2(0.f, 0.f)});
	SpriteM.AddSprite(Sprites::OrcRun_4, {raylib::Rectangle(297, 16, 22, 16), raylib::Vector2(0.f, 0.f)});
	SpriteM.AddSprite(Sprites::OrcRun_5, {raylib::Rectangle(322, 16, 22, 16), raylib::Vector2(0.f, 0.f)});
	SpriteM.AddSprite(Sprites::OrcRun_6, {raylib::Rectangle(345, 16, 22, 16), raylib::Vector2(0.f, 0.f)});
	SpriteM.AddSprite(Sprites::OrcRun_7, {raylib::Rectangle(369, 16, 22, 16), raylib::Vector2(0.f, 0.f)});
	SpriteM.AddSprite(Sprites::OrcRun_8, {raylib::Rectangle(393, 16, 22, 16), raylib::Vector2(0.f, 0.f)});
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

std::optional<Sprite> FindSprite(const std::unordered_map<Sprites::ID, Sprite> &textureRects, Sprites::ID id) {
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
	auto rect = FindSprite(mTextures, id);
	if (!rect.has_value()) {
		return Sprite{};
	}
	return rect.value();
}

void SpriteManager::Draw(Sprites::ID id, raylib::Vector2 position, raylib::Vector2 origin, f32 rotation, bool hflip, bool vflip, f32 scale, Color tint) const {
	auto rect = FindSprite(mTextures, id);
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
		origin.x = sourceRect.width - origin.x;
		sourceRect.width *= -1;
	}
	if (vflip) {
		// origin.y = sourceRect.height;
		sourceRect.height *= -1;
	}

	mTexture.Draw(sourceRect,
				  destRect,
				  origin,
				  //   {destRect.width / 2, destRect.height / 2}, // Origin
				  rotation,
				  tint);
}

void SpriteManager::Draw(Sprites::ID id, raylib::Vector2 position, f32 rotation, bool hflip, bool vflip, f32 scale, Color tint) const {
	auto sprite = FindSprite(mTextures, id);
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
