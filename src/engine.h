#pragma once

#include "graphics.h"

#define AUDIO_QUEUE_LEN 8
#define AUDIO_BUFFER_SIZE 2400
#define RENDER_QUEUE_LEN 16

struct engine {
    uint8_t pixelbuf[Y_RESOLUTION][X_RESOLUTION];
    struct tileset tileset;
    uint32_t *palette;
    uint32_t objbuf[Y_RESOLUTION / BLOCK_SIZE][X_RESOLUTION / BLOCK_SIZE];
};

extern struct engine engine;
