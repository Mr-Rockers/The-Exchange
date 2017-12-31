#ifndef INPUT_H
#define INPUT_H

#include "Game Engine/Utility Classes/Externals.h"

struct Input {
	static void HandleKeyDown(SDL_KeyboardEvent* kE);
	static void HandleKeyUp(SDL_KeyboardEvent* kE);

	enum MovementDirection {Forward, Backward, StrafeLeft, StrafeRight};
	static void HandleMovement(MovementDirection direction);

	static void HandleMouse(SDL_MouseMotionEvent* mME);
	static void HandleMouseButtonDown(SDL_MouseButtonEvent* mBE);
	static void HandleMouseButtonUp(SDL_MouseButtonEvent* mBE);

	static void Update();

};

#endif