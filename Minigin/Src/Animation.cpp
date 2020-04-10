#include "MiniginPCH.h"
#include "Animation.h"

Animation::Animation(unsigned int index, unsigned int numFrames, unsigned int animationSpeed)
{
	m_Index = index;
	m_NumFrames = numFrames;
	m_AnimationSpeed = animationSpeed;
}
