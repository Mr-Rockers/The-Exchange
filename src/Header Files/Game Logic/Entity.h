#ifndef ENT_LOGIC_H
#define ENT_LOGIC_H

#include "Game Engine/Utility Classes/Externals.h"
#include "Game Engine/Render Classes/Render.h"


typedef unsigned int entity_id;

class Entity {
protected:
	entity_id currentID;
	std::string unlocalisedName;

	glm::vec3 position;

public:
	static entity_id ID_INCREMENT; //SERVER SIDE

	Entity() {}
	Entity(std::string unlocalisedName);
	virtual ~Entity();

	entity_id getEntityID();
	std::string getUnlocalisedName();

	void setPosition(glm::vec3 newPos);
	glm::vec3 getPosition();
};

//Automagically registers to entityUpdateableRegister upon creation.
//Instead of position data updating immediately, position is updated whenever 
//the update function is called. This mostly allows for speed and acceleration
//calculations to be performed quickly and easily. These will only be implemented
//when they're needed.
class EntityUpdateable : public Entity {
	glm::vec3 newPosition;
	float deltaTime;
public:
	EntityUpdateable() {}
	EntityUpdateable(std::string unlocalisedName);
	virtual ~EntityUpdateable();

	virtual void update(float deltaTime);
	virtual void postUpdate();

	virtual void draw() {}

	//Sets the entities position on update. Use this instead of manually setting vector.
	void setPosition(glm::vec3 newPos); //OVERRIDE

	//Translates entity via update with deltaTime.
	void translate(glm::vec3 direction);
};
extern std::vector<EntityUpdateable*> ENTITY_UPDATEABLE_REGISTER_EXTRN;

class EntityPlayer : public EntityUpdateable {
protected:
	Render* render;
public:

	float cameraPitch, cameraYaw;
	float walkingSpeed, strafeSpeed;

	bool consoleEnabled;

	EntityPlayer() {}
	EntityPlayer(std::string username);
	virtual ~EntityPlayer();

	void update(float deltaTime);

	void setRender(Render* newRender);
	void draw();
	void drawClientside();

	void rotateCameraInput(int xRel, int yRel);
	void rotateCamera(float pitchMod, float yawMod);

	void enableCursor(bool enabled);
	void toggleConsole();
	
	bool isClient();
	bool isGameInFocus();

	glm::vec3 getRelativeDirection(float pitchMod, float yawMod);
	glm::vec3 getForwardLookDirection();
};

extern EntityPlayer LOCAL_PLAYER;

#endif