#pragma once
#include <SDL.h>

class FPSComponent
{
public:
	FPSComponent() = default;
	~FPSComponent() = default;

	void StartTime();
private:
	static const int DESIRED_FPS = 60;
	static const int MS_PER_SECOND = 1000; //how much milliseconds are in one second
	static const float DESIRED_FRAMERATE;
	
	//static Uint32 m_LastTime;
	//static Uint32 m_CurrentTime;
	//static int m_AccumulatedTime;

};

