#pragma once
#include "Utility\Includes.hpp"

#include <unordered_map>
#include <vector>
#include <string>

struct AnimationFrame {
	Sprites::ID spriteID;
	f32 duration;
};

class Animation {
public:
	Animation() = default;
	Animation(const std::vector<AnimationFrame> &frames, bool looping = true);

	void Update();
	void Reset();

	void Play();
	void Stop();

	Sprites::ID GetCurrentFrame() const { return mFrames[mCurrentFrame].spriteID; }
	bool IsComplete() { return mComplete; }

private:
	std::vector<AnimationFrame> mFrames;
	size_t mCurrentFrame{0};
	f32 mFrameTime{0.f};

	bool mLooping{true};
	bool mComplete{false};

	bool mIsPlaying{false};
};