#pragma once

#include "input.h"

struct rom {
    void (*init)();
    void (*update)(struct input, uint32_t time);
    void (*draw)();
    int running;
};

