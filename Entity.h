#ifndef ENT_LOGIC_H
#define ENT_LOGIC_H

#include "Externals.h"

typedef unsigned int entity_id;

class Entity {
protected:
	entity_id currentID;
	std::string unlocalisedName;

	glm::vec3 position;

public:
	static entity_id ID_INCREMENT; //SERVER SIDE

	Entity(std::string unlocalisedName);
	virtual ~Entity();

	entity_id getEntityID();
	std::string getUnlocalisedName();

	void setPosition(glm::vec3 newPos);
	glm::vec3 getPosition();
};

class EntityUpdateable : public Entity {
	bool hasNewPosition;
	glm::vec3 newPosition, lastPosition;
	float speed, deltaTime;

	void updateSpeed();
public:

	//Automagically registers to entityUpdateableRegister.
	EntityUpdateable(std::string unlocalisedName);
	virtual ~EntityUpdateable();

	virtual void update(float deltaTime);

	//For distance, speed, time calculations, etc.
	virtual void postUpdate();

	//Sets the entities position. Use this instead of manually setting vector.
	void setPosition(glm::vec3 newPos); //OVERRIDE

	//Translates entity at the direction by deltaTime.
	void translate(glm::vec3 direction);

	float getSpeed();
};
extern std::vector<EntityUpdateable*> ENTITY_UPDATEABLE_REGISTER_EXTRN;

class EntityPlayer : public EntityUpdateable {
protected:
	//In Degrees
	bool isClient;
	
public:
	float cameraPitch, cameraYaw;

	EntityPlayer(std::string username, bool isClient);
	virtual ~EntityPlayer();

	void draw();
	void drawClientside();

	glm::vec3 getForwardLookDirection();
};

#endif