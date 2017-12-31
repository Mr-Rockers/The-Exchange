#include "Game Engine/Utility Classes/Externals.h"
#include "Game Engine/Audio Classes/Audio.h"
#include "Game Engine/Render Classes/Render.h"
#include "Game Logic/Entity.h"
#include "Game Logic/Input.h"

EntityPlayer LOCAL_PLAYER = EntityPlayer("localhost");

int main(int argc, char** argv) {
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_TIMER) != 0) {
		return -1;
	}

	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) == -1) {
		std::cout << "SDL Mixer Error - Mix_OpenAudio:\n" << Mix_GetError() << "\n";
		std::cin.get();
		return -1;
	}
	Mix_AllocateChannels(64);

	Render* render = new Render();
	if (render->mainWindow == nullptr || !render->glewInitialised()) {
		return -1;
	}
	LOCAL_PLAYER.setRender(render);

	//AUDIO TESTS
	/*EntityPlayer playerAudioTest = EntityPlayer("Audio Test");
	AudioClip walkingGravelClip = AudioClip("resources/audio/walkingGravel.wav");
	EntityAudioSource testAudioSource = EntityAudioSource(&playerAudioTest, true, true, 10.0f);
	testAudioSource.setPosition(glm::vec3(0.0f, 0.0f, -5.0f));*/

	//PLAYER

	//GL INIT
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glEnable(GL_DEPTH_TEST);

	//RUN VARIABLES
	float startTime = 0.0f, endTime = 0.0f, deltaTime = 0.0f;
	bool run = true;
	while (run) {
		//CALCULATE DELTATIME
		if (endTime != 0 || startTime != 0) {
			deltaTime = (endTime - startTime) / 1000.0f;
		}
		startTime = (float) SDL_GetTicks();

		//UPDATE UPDATEABLE ENTITIES
		for (unsigned int i = 0; i < ENTITY_UPDATEABLE_REGISTER_EXTRN.size(); i++) {
			ENTITY_UPDATEABLE_REGISTER_EXTRN.at(i)->update(deltaTime);
		}

		//INPUT
		SDL_Event e;
		while (SDL_PollEvent(&e)){
			if (e.type == SDL_QUIT) {
				run = false;
			}
			if (e.type == SDL_KEYDOWN) {
				Input::HandleKeyDown(&e.key);
			}
			if (e.type == SDL_KEYUP) {
				Input::HandleKeyUp(&e.key);
			}
			if (e.type == SDL_MOUSEMOTION) {
				Input::HandleMouse(&e.motion);
			}
			if (e.type == SDL_MOUSEBUTTONDOWN) {
				Input::HandleMouseButtonDown(&e.button);
			}
			if (e.type == SDL_MOUSEBUTTONUP) {
				Input::HandleMouseButtonUp(&e.button);
			}
		}
		Input::Update();

		//PHYSICS

		//LOGIC
		//glm::vec3 playerPos = LOCAL_PLAYER.getPosition();
		//std::cout << "Player POS - X:" << playerPos.x << " Y:" << playerPos.y << " Z:" << playerPos.z << "\n";

		//RENDER
		render->update(deltaTime);

		//POST UPDATE
		for (unsigned int i = 0; i < ENTITY_UPDATEABLE_REGISTER_EXTRN.size(); i++) {
			ENTITY_UPDATEABLE_REGISTER_EXTRN.at(i)->postUpdate();
		}
		endTime = (float)SDL_GetTicks();
	}

	Mix_Quit();
	SDL_Quit();
	return 0;
}