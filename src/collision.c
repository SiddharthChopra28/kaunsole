#include "graphics.h"
#include <stdbool.h>

int8_t colliding_x(struct sprite *s1, struct sprite *s2) {
    int16_t x_dist = s2->x + s2->hitbox.x - s1->x - s1->hitbox.x;
    if (x_dist > 0) {
        if (x_dist < s1->hitbox.width)
            return 1;
        else
            return 0;
    } else {
        if (x_dist < -s2->hitbox.width)
            return 0;
        else
            return -1;
    }
}

int8_t colliding_y(struct sprite *s1, struct sprite *s2) {
    int16_t y_dist = s2->y + s2->hitbox.y - s1->y - s1->hitbox.y;
    if (y_dist > 0) {
        if (y_dist < s1->hitbox.height)
            return 1;
        else
            return 0;
    } else {
        if (y_dist < -s2->hitbox.height)
            return 0;
        else
            return -1;
    }
}

bool collidingp(struct sprite *sprite, uint8_t y, uint8_t x) {
    bool x_bound = sprite->x + sprite->hitbox.x < x &&
                   x < (sprite->x + sprite->hitbox.width);
    bool y_bound = sprite->y + sprite->hitbox.y < y &&
                   y < (sprite->y + sprite->hitbox.height);
    return x_bound && y_bound;
}

// bool collide_tile(struct sprite *sprite, )
