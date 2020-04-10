#pragma once
class Animation
{
public:
	unsigned int m_Index;
	unsigned int m_NumFrames;
	unsigned int m_AnimationSpeed;
	Animation() = default;
	Animation(unsigned int index, unsigned int numFrames, unsigned int animationSpeed);
};