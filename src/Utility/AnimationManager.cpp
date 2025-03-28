#include "Animation.hpp"
#include "AnimationManager.hpp"

AnimationManager *AnimationManager::Instance = nullptr;

void AnimationManager::Init() {
	assert(!Instance);
	Instance = new AnimationManager;
	assert(Instance);
}

void AnimationManager::Shutdown() {
	delete Instance;
	Instance = nullptr;
}

void AnimationManager::Update() {
	if (mIsPlaying)
		mAnimations[mCurrentAnimation].Update();
}

void AnimationManager::AddAnimation(Animations::ID id, const Animation &animation) {
	mAnimations[id] = animation;
}

const Animation &AnimationManager::GetAnimation(Animations::ID id) const {
	return mAnimations.at(id);
}

void AnimationManager::Play(Animations::ID id) {
	mCurrentAnimation = id;
	mAnimations.at(id).Reset();
	mIsPlaying = true;
}

void AnimationManager::Stop() {
	mIsPlaying = false;
}
