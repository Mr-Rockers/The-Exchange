#include "Entity.h"

EntityPlayer::EntityPlayer(std::string username, bool isClient) : EntityUpdateable("entity_player"), isClient(isClient), cameraPitch(90.0f), cameraYaw(0.0f) {

}

EntityPlayer::~EntityPlayer() {

}

void EntityPlayer::draw() {

}

void EntityPlayer::drawClientside() {

}

glm::vec3 EntityPlayer::getForwardLookDirection() {

	return glm::vec3(smartSin<float>(this->cameraYaw), smartCos<float>(this->cameraPitch), -smartCos<float>(this->cameraYaw));
}