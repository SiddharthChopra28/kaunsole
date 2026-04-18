#pragma once

enum attributes {
    FLIP_X = 1,
    FLIP_Y = 1 << 1,
};

struct character {};

#define ATTRIB_HAS(sprite, ATTRIB) (sprite->attributes & ATTRIB)
#define ATTRIB_SET(sprite, ATTRIB) (sprite->attributes |= ATTRIB)
#define ATTRIB_TOGGLE(sprite, ATTRIB) (sprite->attributes ^= ATTRIB)
