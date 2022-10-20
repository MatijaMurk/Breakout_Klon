#include "TimerModule.h"

TimerModule* TimerModule::instance = NULL;

TimerModule* TimerModule::Instance() {
	if (instance == NULL)
		instance = new TimerModule();

	return instance;

}

void TimerModule::Release() {

	delete instance;

	instance = NULL;
}

TimerModule::TimerModule() {
	Reset();
	elapsedTick = 0;
	deltaTime = 0.0f;
	timeScale = 1.0f;

}

TimerModule::~TimerModule() {

}

void TimerModule::Reset() {
	
	startTicks = SDL_GetTicks();
	
}

float TimerModule::DeltaTime() {
	return deltaTime;
}

void TimerModule::TimeScale(float t) {

	timeScale = t;
}

float TimerModule::TimeScale() {

	return timeScale;
}
void TimerModule::Update() {
	elapsedTick = SDL_GetTicks() - startTicks;
	deltaTime = elapsedTick * 0.001f;
}