#include <SDL2/SDL_mixer.h>
#include <iostream>
#include <map>

#include "common.hpp"

using namespace std;

map<string, Mix_Chunk*> soundCache;

#define SND_FREQUENCY 44100
#define SND_CHANNELS 2
#define SND_SAMPLE_SIZE 2048

Mix_Chunk* loadSound(string filename) {
	filename = "res/snd/" + filename;

	if (soundCache.count(filename) == 0) {
		Mix_Chunk* snd = Mix_LoadWAV(filename.c_str());

		if (snd == NULL) {
			cout << "failed to load sound: " << filename << endl;
		} else {
			cout << "loaded sound: " << filename << endl;
		}

		soundCache[filename] = snd;
	}

	Mix_Volume(SoundChannel::UI, MIX_MAX_VOLUME / 10);

	return soundCache[filename];
}

void initSound() {
	Mix_Init(MIX_INIT_MOD);

	if (Mix_OpenAudio(SND_FREQUENCY, MIX_DEFAULT_FORMAT, SND_CHANNELS, SND_SAMPLE_SIZE) < 0) {
		cout << "Audio setup failed." << endl;
	} else {
		cout << "Audio setup complete." << endl;
	}

	loadSound("interface/interface1.wav");
}

void quitSound() {
	cout << "quit sound" << endl;

	Mix_Quit();
}

void playSound(string filename, SoundChannel ch) {
	cout << "play sound: " << filename << endl;

	if (Mix_PlayChannel(ch, loadSound(filename), 0) == -1) {
		cout << "failed to play: " << Mix_GetError() << endl;
	}
}
