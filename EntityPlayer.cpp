#include "Entity.h"

EntityPlayer::EntityPlayer(std::string username, Render* render) : EntityUpdateable("entity_player"), render(render) {
	cameraPitch = 90.0f;
	cameraYaw = 0.0f;

	walkingSpeed = 1.0f;
	strafeSpeed = 1.0f;
}

EntityPlayer::~EntityPlayer() {

}

void EntityPlayer::draw() {

}

void EntityPlayer::drawClientside() {

}

void EntityPlayer::translate(glm::vec3 direction) {
	EntityUpdateable::translate(direction);

	if (this->isClient()) {

		this->render->viewMatrix = glm::translate(this->render->viewMatrix, direction);
		if (direction.x != 0.0f) {
			this->render->viewMatrix = glm::translate(this->render->viewMatrix, glm::cross(direction, this->render->UP));
		}
	}
}

bool EntityPlayer::isClient() {
	return this->render != nullptr;
}

glm::vec3 EntityPlayer::getRelativeDirection(float pitchMod, float yawMod) {
	return glm::vec3(smartSin<float>(this->cameraYaw + yawMod), smartCos<float>(this->cameraPitch + pitchMod), smartCos<float>(this->cameraYaw + yawMod));
}

glm::vec3 EntityPlayer::getForwardLookDirection() {
	return this->getRelativeDirection(0.0f, 0.0f);
}