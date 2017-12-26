#include "Audio.h"

AudioClip::AudioClip(std::string location) {
	sample = Mix_LoadWAV(location.c_str());
	this->isLoaded = (sample);
	if (!this->isLoaded) {
		std::cout << "\nFailed to load audio clip. (" << location << ")\nError:\n" << Mix_GetError() << "\n";
	}
}

AudioClip::~AudioClip() {
	if (this->isLoaded) {
		Mix_FreeChunk(this->sample);
		this->sample = nullptr;
		this->isLoaded = false;
	}
}

bool AudioClip::hasData() {
	return this->isLoaded;
}

Mix_Chunk* AudioClip::getData() {
	return this->sample;
}

EntityAudioSource::EntityAudioSource(EntityPlayer* player, bool doppler, bool haas, float spread) : EntityUpdateable("audio_source"), dopplerEffect(doppler), haasEffect(haas), player(player), spread(spread) {
	this->panArguments = new float[3]{ 0.5f, 0.5f, 1.0f };
}

EntityAudioSource::~EntityAudioSource() {}

void EntityAudioSource::calculateEffects() {
	this->pan = 0.0f;
	this->distanceToPlayer = 0.0f;

	if (this->isPlaying()) {

		//std::cout << "Angle between: " << glm::degrees(glm::angle(, )) << "\n";
		glm::vec3 playerForward = this->player->getForwardLookDirection();
		glm::vec3 relativeAudioSourcePos = this->getPosition() - this->player->getPosition();

		//Find the angle between the forward vector and the normalised soundRelative vector.
		float angle = angleBetweenVectors<float>(playerForward.x, playerForward.z, relativeAudioSourcePos.x, relativeAudioSourcePos.z);

		bool isLeft = false; {
			glm::vec3 perpendicular = glm::cross(playerForward, relativeAudioSourcePos);
			float direction = glm::dot(perpendicular, glm::vec3(0.0f, 1.0f, 0.0f));
			isLeft = direction < 0.0f;
		}

		float fixedAngle = fixDegrees<float>(angle * (isLeft ? -1.0f : 1.0f));

		this->pan = (smartSin<float>(fixedAngle) + 1.0f) / 2.0f;

		this->distanceToPlayer = glm::distance(player->getPosition(), this->getPosition());
	}
}

void EntityAudioSource::applyEffects() {

	if (this->isPlaying()) {
		this->panArguments[0] = 1.0f - this->pan;
		this->panArguments[1] = this->pan;
		this->panArguments[2] = 0.1f; //VOLUME

	}
}

void EntityAudioSource::update(float deltaTime) {
	EntityUpdateable::update(deltaTime);

	if (this->isPlaying()) {

		if (Mix_Playing(this->usedChannel) == 0) {
			Mix_UnregisterAllEffects(this->usedChannel);
			this->usedChannel = -1; //Resets isPlaying().
			return;
		}
		calculateEffects();
		applyEffects();
	}
}

void EntityAudioSource::play(AudioClip* audioClip) {
	this->audioClipToPlay = audioClip;

	if (this->audioClipToPlay->hasData()) {
		this->usedChannel = Mix_Playing(-1);

		Mix_PlayChannel(this->usedChannel, this->audioClipToPlay->getData(),0);

		calculateEffects();
		applyEffects();
		Mix_RegisterEffect(this->usedChannel, AudioEffects::pan, NULL, this->panArguments);
	}
}

bool EntityAudioSource::isPlaying() {
	return (this->usedChannel != -1);
}