#include "audio.h"
#include <SDL.h>


SDL_AudioDeviceID dev;
SDL_AudioSpec wav_spec;
Uint8 *wav_buffer;
Uint32 wav_length;

void audio_init() {
    const char *filename = "boom.wav";
    if (SDL_LoadWAV(filename, &wav_spec, &wav_buffer, &wav_length) == NULL) {
        printf("Failed to load WAV: %s\n", SDL_GetError());
        SDL_Quit();
        return;
    }

    wav_spec.callback = NULL;
    wav_spec.userdata = NULL;

    dev = SDL_OpenAudioDevice(NULL, 0, &wav_spec, NULL, 0);
    if (dev == 0) {
        printf("Failed to open audio device: %s\n", SDL_GetError());
        SDL_FreeWAV(wav_buffer);
        SDL_Quit();
        return;
    }

    SDL_PauseAudioDevice(dev, 0);
}

void audio_dispose() {
    SDL_CloseAudioDevice(dev);
    // SDL_FreeWAV(wav_buffer);
}

void audio_play() {
    SDL_ClearQueuedAudio(dev);
    SDL_QueueAudio(dev, wav_buffer, wav_length);
    SDL_PauseAudioDevice(dev, 0);
}