#pragma once

#include <stdint.h>

#define X_RESOLUTION 320
#define Y_RESOLUTION 240

struct render_command {
    uint8_t priority;
};

struct texture {
    uint32_t offset;
};

struct tilemap {
    uint8_t *data;
    uint16_t num_textures;
    struct texture textures[64];
};

struct palette {
    uint8_t r[16];
    uint8_t g[16];
    uint8_t b[16];
};

void load_tilemap(void *);

void draw_text_palette(const char *, uint8_t, uint16_t, uint16_t);
void draw_sprite(uint8_t, uint16_t, uint16_t);
void draw_sprite_palette(uint8_t, uint8_t, uint16_t, uint16_t);
void set_palette(struct palette *, uint8_t);
