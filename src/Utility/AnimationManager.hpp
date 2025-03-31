#pragma once
#include "Utility\Includes.hpp"
#include "Animation.hpp"

class Animation;
class AnimationManager {
public:
	static AnimationManager &GetInstance();

	static void Init();
	static void Shutdown();

	void AddAnimation(Animations::ID id, Animation animation);
	Animation GetAnimation(Animations::ID id);

private:
	AnimationManager() = default;
	~AnimationManager() = default;
	AnimationManager(AnimationManager const &) = delete;
	void operator=(AnimationManager const &) = delete;

	static AnimationManager *Instance;

	std::unordered_map<Animations::ID, Animation> mAnimations;
};

#define AniM AnimationManager::GetInstance()
