#include "Game Logic/Input.h"
#include "Game Logic/Entity.h"

//EntityPlayer LOCAL_PLAYER;
bool dirForward = false, dirBackward = false, dirSLeft = false, dirSRight = false;

void Input::HandleKeyDown(SDL_KeyboardEvent* kE) {

	switch (kE->keysym.sym) {
		case SDLK_w:
			dirForward = true;
			break;
		case SDLK_s:
			dirBackward = true;
			break;
		case SDLK_a:
			dirSLeft = true;
			break;
		case SDLK_d:
			dirSRight = true;
			break;
		case SDLK_TAB:
			LOCAL_PLAYER.toggleConsole();
			break;
		default:
			break;
	}
}

void Input::HandleKeyUp(SDL_KeyboardEvent* kE) {
	switch (kE->keysym.sym) {
	case SDLK_w:
		dirForward = false;
		break;
	case SDLK_s:
		dirBackward = false;
		break;
	case SDLK_a:
		dirSLeft = false;
		break;
	case SDLK_d:
		dirSRight = false;
		break;
	default:
		break;
	}
}

void Input::HandleMovement(MovementDirection direction) {

	if (LOCAL_PLAYER.isGameInFocus()) {
		glm::vec3 perpendicularDirection = glm::vec3(LOCAL_PLAYER.getRelativeDirection(0.0f, 90.0f) * LOCAL_PLAYER.strafeSpeed);

		switch (direction) {
		case MovementDirection::Forward:
			LOCAL_PLAYER.translate(glm::vec3(LOCAL_PLAYER.getForwardLookDirection() * LOCAL_PLAYER.walkingSpeed));
			break;
		case MovementDirection::Backward:
			LOCAL_PLAYER.translate(glm::vec3(LOCAL_PLAYER.getForwardLookDirection() * -LOCAL_PLAYER.walkingSpeed));
			break;
		case MovementDirection::StrafeLeft:
			LOCAL_PLAYER.translate(glm::vec3(-perpendicularDirection.x, 0.0f, -perpendicularDirection.z));
			break;
		case MovementDirection::StrafeRight:
			LOCAL_PLAYER.translate(glm::vec3(perpendicularDirection.x, 0.0f, perpendicularDirection.z));
			break;
		default:
			break;
		}
	}
}

void Input::HandleMouse(SDL_MouseMotionEvent* mME) {

	LOCAL_PLAYER.rotateCameraInput(mME->yrel, mME->xrel);
}

void Input::HandleMouseButtonDown(SDL_MouseButtonEvent* mBE) {
}

void Input::HandleMouseButtonUp(SDL_MouseButtonEvent* mBE) {
}

void Input::Update() {
	if (dirForward) {
		HandleMovement(MovementDirection::Forward);
	}
	if (dirBackward) {
		HandleMovement(MovementDirection::Backward);
	}
	if (dirSLeft) {
		HandleMovement(MovementDirection::StrafeLeft);
	}
	if (dirSRight) {
		HandleMovement(MovementDirection::StrafeRight);
	}
}