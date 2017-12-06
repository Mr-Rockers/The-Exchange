#include "Entity.h"

entity_id Entity::ID_INCREMENT = 0;

Entity::Entity(std::string unlocalisedName) : unlocalisedName(unlocalisedName) {
	this->currentID = Entity::ID_INCREMENT++;
}

Entity::~Entity() {
}

entity_id Entity::getEntityID() {
	return this->currentID;
}

std::string Entity::getUnlocalisedName() {
	return this->unlocalisedName;
}

void Entity::setPosition(glm::vec3 newPos) {
	this->position = newPos;
}

glm::vec3 Entity::getPosition() {
	return this->position;
}