#pragma once

#include "audio.h"
#include "graphics.h"
#include "input.h"

#define AUDIO_QUEUE_LEN 8
#define AUDIO_BUFFER_SIZE 2400
#define RENDER_QUEUE_LEN 16

struct engine {
    struct audio_event audio_queue[AUDIO_QUEUE_LEN];
    struct render_command render_queue[RENDER_QUEUE_LEN];
    uint32_t framebuffer[Y_RESOLUTION][X_RESOLUTION]; // RGBA32
    uint8_t audio_buffer[AUDIO_BUFFER_SIZE];
    struct {
        uint32_t readindex;
        uint32_t writeindex;
    } audio_ring;
    struct tilemap tilemap;
    struct palette palettes[8];
};

extern struct engine engine;
