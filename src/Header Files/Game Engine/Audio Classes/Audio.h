#ifndef AUDIO_H
#define AUDIO_H

#include "Game Engine/Utility Classes/Externals.h"
#include "Game Engine/Audio Classes/AudioEffects.h"
#include "Game Logic/Entity.h"

class AudioClip {
	Mix_Chunk* sample;
	bool isLoaded;
public:
	AudioClip(std::string location);
	virtual ~AudioClip();

	bool hasData();
	Mix_Chunk* getData();
};

class EntityAudioSource : public EntityUpdateable {
protected:
	AudioClip* audioClipToPlay;
	EntityPlayer* player;
	bool dopplerEffect, haasEffect;
	float pan, distanceToPlayer, spread;
	int usedChannel;

	//Arguments for AudioEffects::pan
	float* panArguments;

public:
	EntityAudioSource(EntityPlayer* player, bool doppler, bool haas, float spread);
	virtual ~EntityAudioSource();

	virtual void update(float deltaTime);
	void play(AudioClip* audioClip);
	void calculateEffects();
	void applyEffects();

	bool isPlaying();
};

#endif