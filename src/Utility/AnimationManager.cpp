#include "AnimationManager.hpp"
#include "Animation.hpp"

AnimationManager *AnimationManager::Instance = nullptr;

void AnimationManager::Init() {
	assert(!Instance);
	Instance = new AnimationManager;
	assert(Instance);

	std::vector<AnimationFrame> soldierIdleFrames = {
		{Sprites::SoldierIdle_1, 0.1f},
		{Sprites::SoldierIdle_2, 0.1f},
		{Sprites::SoldierIdle_3, 0.1f},
		{Sprites::SoldierIdle_4, 0.1f},
		{Sprites::SoldierIdle_5, 0.1f},
		{Sprites::SoldierIdle_6, 0.1f}};
	AniM.AddAnimation(Animations::ID::SoldierIdle, Animation(soldierIdleFrames));

	std::vector<AnimationFrame> soldierAttack1Frames = {
		{Sprites::SoldierAttack1_1, 0.1f},
		{Sprites::SoldierAttack1_2, 0.1f},
		{Sprites::SoldierAttack1_3, 0.1f},
		{Sprites::SoldierAttack1_4, 0.1f},
		{Sprites::SoldierAttack1_5, 0.1f},
		{Sprites::SoldierAttack1_6, 0.1f}};
	AniM.AddAnimation(Animations::ID::SoldierAttack1, Animation(soldierAttack1Frames, false));

	std::vector<AnimationFrame> soldierRunFrames = {
		{Sprites::SoldierRun_1, 0.1f},
		{Sprites::SoldierRun_2, 0.1f},
		{Sprites::SoldierRun_3, 0.1f},
		{Sprites::SoldierRun_4, 0.1f},
		{Sprites::SoldierRun_5, 0.1f},
		{Sprites::SoldierRun_6, 0.1f},
		{Sprites::SoldierRun_7, 0.1f},
		{Sprites::SoldierRun_8, 0.1f}};
	AniM.AddAnimation(Animations::ID::SoldierRun, Animation(soldierRunFrames));

	std::vector<AnimationFrame> orcIdleFrames = {
		{Sprites::OrcIdle_1, 0.1f},
		{Sprites::OrcIdle_2, 0.1f},
		{Sprites::OrcIdle_3, 0.1f},
		{Sprites::OrcIdle_4, 0.1f},
		{Sprites::OrcIdle_5, 0.1f},
		{Sprites::OrcIdle_6, 0.1f}};
	AniM.AddAnimation(Animations::ID::OrcIdle, Animation(orcIdleFrames));

	std::vector<AnimationFrame> orcRunFrames = {
		{Sprites::OrcRun_1, 0.1f},
		{Sprites::OrcRun_2, 0.1f},
		{Sprites::OrcRun_3, 0.1f},
		{Sprites::OrcRun_4, 0.1f},
		{Sprites::OrcRun_5, 0.1f},
		{Sprites::OrcRun_6, 0.1f},
		{Sprites::OrcRun_7, 0.1f},
		{Sprites::OrcRun_8, 0.1f}};
	AniM.AddAnimation(Animations::ID::OrcRun, Animation(orcRunFrames));
}

void AnimationManager::Shutdown() {
	delete Instance;
	Instance = nullptr;
}

void AnimationManager::AddAnimation(Animations::ID id, Animation animation) {
	animation.SetID(id);
	mAnimations[id] = animation;
}

Animation AnimationManager::GetAnimation(Animations::ID id) {
	return mAnimations.at(id);
}

AnimationManager &AnimationManager::GetInstance() {
	assert(Instance);
	return *Instance;
}
