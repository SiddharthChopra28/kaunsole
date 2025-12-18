#include <SDL3/SDL.h>
#include <SDL3/SDL_render.h>
#include <SDL3/SDL_scancode.h>
#include <dirent.h>
#include <stdio.h>

#include "../backend.h"
#include "../graphics.h"

#define SDL_WINDOW_HEIGHT 1080
#define SDL_WINDOW_WIDTH 1920

SDL_Window *window;
SDL_Renderer *renderer;
SDL_Texture *texture;
SDL_AudioStream *audio_stream;

void backend_init() {
    if (!SDL_Init(SDL_INIT_VIDEO | SDL_INIT_JOYSTICK)) {
        SDL_Log("Couldn't initialize SDL: %s", SDL_GetError());
    }
    if (!SDL_CreateWindowAndRenderer("examples/demo/snake", SDL_WINDOW_WIDTH, SDL_WINDOW_HEIGHT, SDL_WINDOW_RESIZABLE, &window, &renderer)) {
    }
    SDL_SetRenderLogicalPresentation(renderer, SDL_WINDOW_WIDTH, SDL_WINDOW_HEIGHT, SDL_LOGICAL_PRESENTATION_LETTERBOX);
    texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA32, SDL_TEXTUREACCESS_STREAMING, X_RESOLUTION, Y_RESOLUTION); 
    SDL_SetTextureScaleMode(texture, SDL_SCALEMODE_NEAREST);

    SDL_AudioSpec spec = {
        .format = SDL_AUDIO_S16,
        .channels = 1,
        .freq = 48000, // 800 samples per frame
    };
    audio_stream = SDL_OpenAudioDeviceStream(SDL_AUDIO_DEVICE_DEFAULT_PLAYBACK, &spec, NULL, NULL);
    SDL_ResumeAudioStreamDevice(audio_stream); 
}

void backend_deinit() {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_DestroyAudioStream(audio_stream); 
}

void backend_render(uint32_t framebuffer[Y_RESOLUTION][X_RESOLUTION]) {
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
    SDL_RenderClear(renderer);
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
    SDL_UpdateTexture(texture, NULL, framebuffer, X_RESOLUTION * 4); 
    SDL_RenderTexture(renderer, texture, NULL, NULL);
    SDL_RenderPresent(renderer);
}

void backend_audio(const void *buffer, uint16_t length) {
    SDL_PutAudioStreamData(audio_stream, buffer, length); 
}

uint32_t backend_time() {
    return SDL_GetTicks();
}

struct input backend_input() {
    struct input input = {0};
    SDL_Event event;
    while(SDL_PollEvent(&event)) {
        switch (event.type) {
        // case SDL_EVENT_QUIT:
        case SDL_EVENT_KEY_DOWN:
            switch (event.key.scancode) {
                case SDL_SCANCODE_UP:
                    input.y = -1;
                    break;
                case SDL_SCANCODE_DOWN:
                    input.y = 1;
                    break;
                case SDL_SCANCODE_LEFT:
                    input.x = -1;
                    break;
                case SDL_SCANCODE_RIGHT:
                    input.x = 1;
                    break;
                case SDL_SCANCODE_A:
                    input.a = true;
                    break;
                case SDL_SCANCODE_B:
                    input.b = true;
                    break;
                default:
                    break;
            }
            break;
        }
    }
    return input;
    // int numkeys;
    // const bool *keystate = SDL_GetKeyboardState(&numkeys);

    // return (struct input) {
    //     .a = keystate[SDL_SCANCODE_A],
    //     .b = keystate[SDL_SCANCODE_B],
    //     .x = (keystate[SDL_SCANCODE_A] ? -1 : keystate[SDL_SCANCODE_D] ? 1 : 0),
    //     .y = (keystate[SDL_SCANCODE_S] ? -1 : keystate[SDL_SCANCODE_W] ? 1 : 0),
    // };
}

uint8_t backend_load_roms(char paths[8][64]) {
    DIR *dir = opendir("build/roms");

    struct dirent *ent;
    uint8_t i = 0;
    while ((ent = readdir(dir))) {
        if (ent->d_type == DT_REG) {
            snprintf(paths[i], 64, "build/roms/%s", ent->d_name);
            i++;
        }
    }
    closedir(dir);
    return i;
}

void backend_sleep(uint32_t ms) {
    SDL_Delay(ms);
}
