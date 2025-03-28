#pragma once
#include "Utility\Includes.hpp"
#include "Animation.hpp"

class AnimationManager {
public:
	static AnimationManager &GetInstance();

	void Init();
	void Shutdown();

	void Update();

	void AddAnimation(Animations::ID id, const Animation &animation);
	const Animation &GetAnimation(Animations::ID id) const;

	void Play(Animations::ID id);
	void Stop();

	Textures::ID GetCurrentAnimationFrame() const { return mAnimations.at(mCurrentAnimation).GetCurrentFrame(); }

private:
	AnimationManager() = default;
	~AnimationManager() = default;
	AnimationManager(AnimationManager const &) = delete;
	void operator=(AnimationManager const &) = delete;

	static AnimationManager *Instance;

	std::unordered_map<Animations::ID, Animation> mAnimations;
	Animations::ID mCurrentAnimation;
	bool mIsPlaying{false};
};