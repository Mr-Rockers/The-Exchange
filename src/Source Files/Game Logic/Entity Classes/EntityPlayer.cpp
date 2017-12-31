#include "Game Logic/Entity.h"

EntityPlayer::EntityPlayer(std::string username) : EntityUpdateable("entity_player") {
	render = nullptr;
	
	cameraPitch = 90.0f;
	cameraYaw = 0.0f;

	walkingSpeed = 10.0f;
	strafeSpeed = 8.0f;

	consoleEnabled = false;
}

EntityPlayer::~EntityPlayer() {

}

void EntityPlayer::update(float deltaTime) {
	EntityUpdateable::update(deltaTime);
}

void EntityPlayer::setRender(Render* newRender) {
	this->render = newRender;

	if (this->isClient()) {
		SDL_SetRelativeMouseMode(SDL_TRUE);
		SDL_ShowCursor(0);
	}
}

void EntityPlayer::draw() {
	if (this->isClient()) {
		this->drawClientside();
		return;
	}
}

void EntityPlayer::drawClientside() {
	if (this->isClient()) {
		
	}
}

void EntityPlayer::rotateCameraInput(int xRel, int yRel) {
	if (this->isClient()) {
		if (this->isGameInFocus()) {
			this->rotateCamera((float)xRel, (float)yRel);
		}
	}
}

void EntityPlayer::rotateCamera(float pitchMod, float yawMod) {
	if (this->isClient()) {
		this->cameraPitch = glm::clamp(this->cameraPitch + pitchMod, 0.0f, 180.0f);
		this->cameraYaw = fixDegrees<float>(this->cameraYaw + yawMod);
	}
}

glm::vec2 lastMousePos = glm::vec2(0.5f, 0.5f);
void EntityPlayer::enableCursor(bool enabled) {
	if (this->isClient()) {

		SDL_SetRelativeMouseMode(enabled ? SDL_FALSE : SDL_TRUE);

		/*STORES/RESTORES LAST MOUSE POSITION*/
		int windowWidth = 0, windowHeight = 0;
		SDL_GetWindowSize(render->mainWindow, &windowWidth, &windowHeight);
		if (enabled) {
			SDL_WarpMouseInWindow(render->mainWindow,
				(int)((float)windowWidth * lastMousePos.x),
				(int)((float)windowHeight * lastMousePos.y));
		}
		else {
			int mouseX = 0, mouseY = 0;
			SDL_GetMouseState(&mouseX, &mouseY);
			lastMousePos = glm::vec2((float)mouseX / (float)windowWidth,
									 (float)mouseY / (float)windowHeight);
		}
		///////////////////////////////////////

		SDL_ShowCursor(enabled ? 1 : 0);
	}
}

void EntityPlayer::toggleConsole() {
	if (this->isClient()) {
		this->consoleEnabled = !this->consoleEnabled;
		this->enableCursor(this->consoleEnabled); //If gameAccess is true, we don't want the cursor.
	}
}

bool EntityPlayer::isClient() {
	return this->render != nullptr;
}

bool EntityPlayer::isGameInFocus() {
	return !this->consoleEnabled;
}

glm::vec3 EntityPlayer::getRelativeDirection(float pitchMod, float yawMod) {
	return glm::vec3(smartSin<float>(this->cameraYaw + yawMod), smartCos<float>(glm::clamp((this->cameraPitch + pitchMod), 0.0f, 180.0f)), -smartCos<float>(this->cameraYaw + yawMod));
}

glm::vec3 EntityPlayer::getForwardLookDirection() {
	return this->getRelativeDirection(0.0f, 0.0f);
}