#pragma once
#include <SDL.h>

class TimerModule
{
private:
	static TimerModule* instance;

	unsigned int startTicks;
	unsigned int elapsedTick;
	float deltaTime;
	float timeScale;

public:
	static TimerModule* Instance();
	static void Release();

	void Reset();
	float DeltaTime();

	void TimeScale(float t);
	float TimeScale();

	void Update();

private:

	TimerModule();
	~TimerModule();

};

