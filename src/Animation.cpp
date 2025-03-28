#include "Animation.hpp"

Animation::Animation(const std::vector<AnimationFrame> &frames, bool looping)
	: mFrames(frames),
	  mLooping(looping) {
}

void Animation::Update() {
	if (mComplete)
		return;
	mFrameTime += GetFrameTime();

	while (mFrameTime >= mFrames[mCurrentFrame].duration) {
		mFrameTime -= mFrames[mCurrentFrame].duration;
		if (mCurrentFrame++ >= mFrames.size()) {
			if (mLooping) {
				mCurrentFrame = 0;
			} else {
				mCurrentFrame = mFrames.size() - 1;
				mComplete = true;
				break;
			}
		}
	}
}

void Animation::Reset() {
	mCurrentFrame = 0;
	mFrameTime = 0.f;
	mComplete = false;
}
