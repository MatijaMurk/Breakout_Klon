#include "InputManager.h"

InputManager* InputManager::sInstance = NULL;

InputManager* InputManager::Instance() {

	if (sInstance == NULL) {
		sInstance = new InputManager();
	}
	return sInstance;
}

void InputManager::Release() {

	delete sInstance;
	sInstance = NULL;

}

InputManager::InputManager(){}
InputManager::~InputManager() {}

bool InputManager::KeyDown(SDL_Scancode scanCode) {

	return mKeyStates[scanCode];

}

void InputManager::Update()
{
	mKeyStates = SDL_GetKeyboardState(NULL);

}
