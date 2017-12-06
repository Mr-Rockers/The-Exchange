#include "Entity.h"

std::vector<EntityUpdateable*> ENTITY_UPDATEABLE_REGISTER_EXTRN = std::vector<EntityUpdateable*>();

EntityUpdateable::EntityUpdateable(std::string unlocalisedName) : Entity(unlocalisedName), hasNewPosition(false) {
	ENTITY_UPDATEABLE_REGISTER_EXTRN.push_back((EntityUpdateable*)this);

}

EntityUpdateable::~EntityUpdateable() {

}

void EntityUpdateable::update(float deltaTime) {
	this->deltaTime = deltaTime;

	if (this->hasNewPosition) {
		this->position = this->newPosition;
		this->newPosition = glm::vec3(0.0f, 0.0f, 0.0f);
		this->hasNewPosition = false;
	}
}

void EntityUpdateable::postUpdate() {
	this->updateSpeed();
	this->lastPosition = this->position;
}

void EntityUpdateable::setPosition(glm::vec3 newPos) {
	this->newPosition = newPos;
	this->hasNewPosition = true;
}

void EntityUpdateable::translate(glm::vec3 direction) {
	this->setPosition(this->getPosition() + (glm::vec3)(direction * this->deltaTime));
}

void EntityUpdateable::updateSpeed() {
	this->speed = 0;
	if (this->deltaTime != 0 && this->position != this->lastPosition) {
		float distance = glm::distance(this->position, this->lastPosition);
		this->speed = distance / this->deltaTime;
	}
}

float EntityUpdateable::getSpeed() {
	return this->speed;
}