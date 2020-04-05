#include "MiniginPCH.h"
#include "FPSComponent.h"

const Uint32 FPSComponent::DESIRED_FPS = 60U;
const Uint32 FPSComponent::MS_PER_SECOND = 1000U;
const Uint32 FPSComponent::COOLDOWN_TIME = FPSComponent::MS_PER_SECOND / 4;
const Uint32 FPSComponent::DESIRED_FRAMERATE = MS_PER_SECOND / DESIRED_FPS;

Uint32 FPSComponent::m_LastTime = 0;
Uint32 FPSComponent::m_StartTime = 0;
Uint32 FPSComponent::m_AccumulatedTime = 0;
int FPSComponent::m_DelayTime = 0;
int FPSComponent::m_FPS = 0;

float FPSComponent::m_ElapsedSec = 0;

float FPSComponent::GetElapsedTime() const
{
	return float(m_StartTime - m_LastTime);
}

int FPSComponent::GetFPS() const
{
	return 0;
}

void FPSComponent::SetStartTime()
{
	m_StartTime = SDL_GetTicks();
}

void FPSComponent::UpdateStartTime()
{
	m_StartTime = m_LastTime;
}

void FPSComponent::SetLastTime()
{
	m_LastTime = SDL_GetTicks();
}
