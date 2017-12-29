#include "Game Engine/Audio Classes/AudioEffects.h"

AudioEffectProgram AudioEffects::pan(int chan, void* stream, int len, void* udata) {
	float* args = (float*)udata;

	if (args == nullptr) {
		std::cout << "No arguments have been supplied to customPanEffect on audio channel " << chan << ".\n";
	}

	Sint16* data = (Sint16*)stream;
	len /= 4;

	for (int sample = 0; sample < len; sample++) {
		data[sample * 2] = (Sint16)(((float)data[sample * 2]) * args[0] * args[2]);
		data[(sample * 2) + 1] = (Sint16)(((float)data[(sample * 2) + 1]) * args[1] * args[2]);
	}
}