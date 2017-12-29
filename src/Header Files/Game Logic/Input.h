#ifndef INPUT_H
#define INPUT_H

#include "Game Engine/Utility Classes/Externals.h"
#include "Game Logic/Entity.h"

struct Input {
	static void HandleKeyDown(EntityPlayer* player, SDL_KeyboardEvent* kE);
	static void HandleKeyUp(EntityPlayer* player, SDL_KeyboardEvent* kE);

	enum MovementDirection {Forward, Backward, StrafeLeft, StrafeRight};
	static void HandleMovement(EntityPlayer* player, MovementDirection direction);

	static void HandleMouse(EntityPlayer* player, SDL_MouseMotionEvent* mME);
	static void HandleMouseButtonDown(EntityPlayer* player, SDL_MouseButtonEvent* mBE);
	static void HandleMouseButtonUp(EntityPlayer* player, SDL_MouseButtonEvent* mBE);

	static void Update(EntityPlayer* player);

};

#endif