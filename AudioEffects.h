#ifndef AUDIO_EFFECTS_H
#define AUDIO_EFFECTS_H

#ifndef AudioEffectProgram
#define AudioEffectProgram void
#endif

#include "Externals.h"

namespace AudioEffects {
	//Pans the audio.
	//ARG0 = Left Channel (normalised float)
	//ARG1 = Right Channel (normalised float)
	//ARG2 = Volume (normalised float)
	AudioEffectProgram pan(int chan, void *stream, int len, void* udata);
}

#endif