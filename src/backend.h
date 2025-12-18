#pragma once

#include "audio.h"
#include "graphics.h"
#include "input.h"

void backend_init();
void backend_render(uint32_t framebuffer[Y_RESOLUTION][X_RESOLUTION]);
void backend_audio(const void *buffer, uint16_t length);
struct input backend_input();
uint32_t backend_time();
void backend_sleep(uint32_t);
uint8_t backend_load_roms(char paths[8][64]);
