#pragma once

#include <stdbool.h>
#include <stdint.h>

#include "graphics.h"

bool colliding_x(struct sprite *s1, struct sprite *s2);
bool colliding_y(struct sprite *s1, struct sprite *s2);
