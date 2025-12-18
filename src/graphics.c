#include "graphics.h"
#include <stdint.h>
#include "engine.h"

void set_palette(struct palette *palette, uint8_t index) {
    engine.palettes[index] = *palette;
} 

void load_tilemap(void *_data) {
    uint8_t *data = _data;
    engine.tilemap.data = data;

    engine.tilemap.num_textures = data[0];
    uint32_t offset = 1;
    for (uint8_t i = 0; i < engine.tilemap.num_textures; i++) {
        engine.tilemap.textures[i].offset = offset;
        uint8_t len = data[offset];
        offset += len * len + 1;
    }
}

void draw_text_palette(const char *text, uint8_t palette, uint16_t y, uint16_t x) {
    while (*(text++)) {
        uint8_t c = (*text) - 'A';
        draw_sprite_palette(c, palette, y, x);
        x += 8;
    }
}

void draw_sprite(uint8_t sprite, uint16_t y, uint16_t x) {
    draw_sprite_palette(sprite, 0, y, x); 
}

void draw_sprite_palette(uint8_t sprite, uint8_t palette, uint16_t y, uint16_t x) {
    uint32_t offset = engine.tilemap.textures[sprite].offset;
    uint8_t len = engine.tilemap.data[offset];
    for (int i = 0; i < len; i++) {
        uint8_t *row = &engine.tilemap.data[offset + 1 + i * len];
        for (int j = 0; j < len; j++) {
            if (!row[j])
                continue;

            uint8_t r = engine.palettes[palette].r[row[j]];
            uint8_t g = engine.palettes[palette].g[row[j]];
            uint8_t b = engine.palettes[palette].b[row[j]];
            engine.framebuffer[y + i][x + j] = r << 24 | g << 16 | b << 8 | 255;
        }
    }
}

