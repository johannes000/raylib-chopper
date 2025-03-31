#include "AnimationManager.hpp"
#include "Animation.hpp"

AnimationManager *AnimationManager::Instance = nullptr;

void AnimationManager::Init() {
	assert(!Instance);
	Instance = new AnimationManager;
	assert(Instance);

	std::vector<AnimationFrame> soldierIdleFrames = {
		{Sprites::SoldierIdle_1, 0.2f},
		{Sprites::SoldierIdle_2, 0.2f},
		{Sprites::SoldierIdle_3, 0.2f},
		{Sprites::SoldierIdle_4, 0.2f},
		{Sprites::SoldierIdle_5, 0.2f},
		{Sprites::SoldierIdle_6, 0.2f}};
	AniM.AddAnimation(Animations::ID::SoldierIdle, Animation(soldierIdleFrames));

	std::vector<AnimationFrame> orcIdleFrames = {
		{Sprites::OrcIdle_1, 0.2f},
		{Sprites::OrcIdle_2, 0.2f},
		{Sprites::OrcIdle_3, 0.2f},
		{Sprites::OrcIdle_4, 0.2f},
		{Sprites::OrcIdle_5, 0.2f},
		{Sprites::OrcIdle_6, 0.2f}};
	AniM.AddAnimation(Animations::ID::OrcIdle, Animation(orcIdleFrames));
}

void AnimationManager::Shutdown() {
	delete Instance;
	Instance = nullptr;
}

void AnimationManager::AddAnimation(Animations::ID id, Animation animation) {
	mAnimations[id] = animation;
}

Animation AnimationManager::GetAnimation(Animations::ID id) {
	return mAnimations.at(id);
}

AnimationManager &AnimationManager::GetInstance() {
	assert(Instance);
	return *Instance;
}
