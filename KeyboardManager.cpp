#include "KeyboardManager.h"

KeyboardManager* KeyboardManager::m_instance = 0;
KeyboardManager::KeyboardManager() {}

KeyboardManager* KeyboardManager::instance() {
	if (m_instance == 0)
		m_instance = new KeyboardManager();
    return m_instance;
}

bool KeyboardManager::IsKeyDown(key k) {
  SDL_Event event;
    while( SDL_PollEvent(&event)) {
        switch(event.type) {
		case SDL_KEYDOWN:
			keyboardState[event.key.keysym.sym] = true;
			break;
		case SDL_KEYUP:
			keyboardState[event.key.keysym.sym] = false;
			break;
		case SDL_MOUSEBUTTONDOWN:
			keyboardState[0] = true;
			break;
		case SDL_MOUSEBUTTONUP:
			keyboardState[0] = false;
        }
    }
	if (k==KeyboardManager::ESC && keyboardState[SDLK_ESCAPE] == true)
		return true;
	if (k==KeyboardManager::D && keyboardState[SDLK_d] == true)
		return true;
	if (k==KeyboardManager::A && keyboardState[SDLK_a] == true)
		return true;
	if (k==KeyboardManager::SPACE && keyboardState[SDLK_SPACE] == true)
		return true;
	if (k==KeyboardManager::MOUSE && keyboardState[0] == true)
		return true;
	else return false;
}