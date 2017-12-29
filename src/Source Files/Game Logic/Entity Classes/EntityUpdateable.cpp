#include "Game Logic/Entity.h"

std::vector<EntityUpdateable*> ENTITY_UPDATEABLE_REGISTER_EXTRN = std::vector<EntityUpdateable*>();

EntityUpdateable::EntityUpdateable(std::string unlocalisedName) : Entity(unlocalisedName){
	ENTITY_UPDATEABLE_REGISTER_EXTRN.push_back((EntityUpdateable*)this);

}

EntityUpdateable::~EntityUpdateable() {

}

void EntityUpdateable::update(float deltaTime) {
	this->deltaTime = deltaTime;
	Entity::setPosition(this->newPosition);
	this->newPosition = Entity::getPosition();
}

void EntityUpdateable::postUpdate() {
}

void EntityUpdateable::setPosition(glm::vec3 newPos) {
	this->newPosition = newPos;
}

void EntityUpdateable::translate(glm::vec3 direction) {
	this->newPosition += direction * this->deltaTime;
}