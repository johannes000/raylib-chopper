#include "Animation.hpp"
#include "AnimationManager.hpp"

AnimationManager *AnimationManager::Instance = nullptr;

void AnimationManager::Init() {
	assert(!Instance);
	Instance = new AnimationManager;
	assert(Instance);

	std::vector<AnimationFrame> idleFrames = {
		{Sprites::PlayerIdle_1, 0.2f},
		{Sprites::PlayerIdle_2, 0.2f},
		{Sprites::PlayerIdle_3, 0.2f},
		{Sprites::PlayerIdle_4, 0.2f},
		{Sprites::PlayerIdle_5, 0.2f},
		{Sprites::PlayerIdle_6, 0.2f}};
	AniM.AddAnimation(Animations::ID::PlayerIdle, idleFrames);
}

void AnimationManager::Shutdown() {
	delete Instance;
	Instance = nullptr;
}

void AnimationManager::AddAnimation(Animations::ID id, const Animation &animation) {
	mAnimations[id] = animation;
}

Animation AnimationManager::GetAnimation(Animations::ID id) const {
	return mAnimations.at(id);
}

AnimationManager &AnimationManager::GetInstance() {
	assert(Instance);
	return *Instance;
}
