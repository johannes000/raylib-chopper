#pragma once
#include "Utility\Includes.hpp"

#include <unordered_map>
#include <vector>
#include <string>

struct AnimationFrame {
	Textures::ID textureID;
	f32 duration;
};

class Animation {
public:
	Animation() = default;
	Animation(const std::vector<AnimationFrame> &frames, bool looping = true);

	void Update();
	void Reset();

	Textures::ID GetCurrentFrame() const { return mFrames[mCurrentFrame].textureID; }
	bool IsComplete() { return mComplete; }

private:
	std::vector<AnimationFrame> mFrames;
	i32 mCurrentFrame{0};
	f32 mFrameTime{0.f};
	bool mLooping{true};
	bool mComplete{false};
};