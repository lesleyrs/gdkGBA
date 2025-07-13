#pragma once
#ifndef __wasm
#include <SDL2/SDL.h>
#include <SDL2/SDL_audio.h>

extern SDL_Window *window;
extern SDL_Renderer *renderer;
extern SDL_Texture *texture;

extern int32_t tex_pitch;
#endif

void platform_init();
void platform_uninit();
