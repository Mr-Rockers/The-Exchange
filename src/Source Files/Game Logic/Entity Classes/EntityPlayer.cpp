#include "Game Logic/Entity.h"

EntityPlayer::EntityPlayer(std::string username, Render* render) : EntityUpdateable("entity_player"), render(render) {
	cameraPitch = 90.0f;
	cameraYaw = 0.0f;

	walkingSpeed = 10.0f;
	strafeSpeed = 8.0f;
}

EntityPlayer::~EntityPlayer() {

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

void EntityPlayer::translate(glm::vec3 direction) {
	EntityUpdateable::translate(direction);

}

void EntityPlayer::rotateCamera(float pitchMod, float yawMod) {
	if (this->isClient()) {
		this->cameraPitch = glm::clamp(this->cameraPitch + pitchMod, 0.0f, 180.0f);
		this->cameraYaw = fixDegrees<float>(this->cameraYaw + yawMod);
	}
}

bool EntityPlayer::isClient() {
	return this->render != nullptr;
}

glm::vec3 EntityPlayer::getRelativeDirection(float pitchMod, float yawMod) {
	return glm::vec3(smartSin<float>(this->cameraYaw + yawMod), smartCos<float>(glm::clamp((this->cameraPitch + pitchMod), 0.0f, 180.0f)), -smartCos<float>(this->cameraYaw + yawMod));
}

glm::vec3 EntityPlayer::getForwardLookDirection() {
	return this->getRelativeDirection(0.0f, 0.0f);
}