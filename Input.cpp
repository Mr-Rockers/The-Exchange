#include "Input.h"

bool dirForward = false, dirBackward = false, dirSLeft = false, dirSRight = false;

void Input::HandleKeyDown(EntityPlayer* player, SDL_KeyboardEvent* kE) {
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
		default:
			break;
	}
}

void Input::HandleKeyUp(EntityPlayer* player, SDL_KeyboardEvent* kE) {
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

void Input::HandleMovement(EntityPlayer* player, MovementDirection direction) {
	glm::vec3 perpendicularDirection = glm::vec3(player->getRelativeDirection(0.0f, 90.0f) * player->strafeSpeed);

	switch (direction) {
		case MovementDirection::Forward:
			player->translate(glm::vec3(player->getForwardLookDirection() * player->walkingSpeed));
			break;
		case MovementDirection::Backward:
			player->translate(glm::vec3(player->getForwardLookDirection() * -player->walkingSpeed));
			break;
		case MovementDirection::StrafeLeft:
			player->translate(glm::vec3(-perpendicularDirection.x, 0.0f, -perpendicularDirection.z));
			break;
		case MovementDirection::StrafeRight:
			player->translate(glm::vec3(perpendicularDirection.x, 0.0f, perpendicularDirection.z));
			break;
		default:
			break;
	}
}

void Input::HandleMouse(EntityPlayer* player, SDL_MouseMotionEvent* mME) {

	player->rotateCamera(mME->yrel, mME->xrel);

}

void Input::HandleMouseButtonDown(EntityPlayer* player, SDL_MouseButtonEvent* mBE) {
}

void Input::HandleMouseButtonUp(EntityPlayer* player, SDL_MouseButtonEvent* mBE) {
}

void Input::Update(EntityPlayer* player) {
	if (dirForward) {
		HandleMovement(player, MovementDirection::Forward);

	}
	if (dirBackward) {
		HandleMovement(player, MovementDirection::Backward);
	}
	if (dirSLeft) {
		HandleMovement(player, MovementDirection::StrafeLeft);
	}
	if (dirSRight) {
		HandleMovement(player, MovementDirection::StrafeRight);
	}
}
