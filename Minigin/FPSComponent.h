#pragma once
#include <SDL.h>

class FPSComponent
{
public:
	FPSComponent() = default;
	~FPSComponent() = default;

	float GetElapsedTime() const;
	int GetFPS() const;

	void SetStartTime();
	void SetLastTime();
	void UpdateStartTime();
private:
	static const Uint32 DESIRED_FPS;
	static const Uint32 MS_PER_SECOND;
	static const Uint32 DESIRED_FRAMERATE;
	static const Uint32 COOLDOWN_TIME;
	
	static Uint32 m_LastTime;
	static Uint32 m_StartTime;
	static Uint32 m_AccumulatedTime;
	static int m_DelayTime;
	static int m_FPS;

	static float m_ElapsedSec;

};

