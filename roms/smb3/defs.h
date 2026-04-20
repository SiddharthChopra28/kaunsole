#pragma once

#include "../../src/graphics.h"

#define TILESET_ROW_OFFSET 16
#define TILESET_PAGE_OFFSET (TILESET_ROW_OFFSET * 32)

#define CLAMP(a, b, c) (a < b ? b : (a < c ? a : c))

#define CLAMP_SET(a, b, c) { \
    if (a > b) { \
        b = a; \
    } else if (b > c) { \
        b = c; \
    } \
}

#define ABS(a) (a < 0 ? -a : a)
#define MIN(a, b) ((a) < (b) ? (a) : (b))
#define MAX(a, b) ((a) > (b) ? (a) : (b))

#define TILE(page, row, column)                                                \
    (page * TILESET_PAGE_OFFSET + row * TILESET_ROW_OFFSET + column)

struct entity {
    struct sprite sprite;
    int8_t x_dir;
    float y_vel;
    float x_vel;
    float x_accel;
    float y_accel;
    float x_accumulator;
    float y_accumulator;
    bool falling;
    uint8_t holding;
};

