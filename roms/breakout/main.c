#include "../../src/rom.h"
#include "../../src/engine.h"
#include "../../src/util.h"
#include <stdbool.h>
#include <stdint.h>
#include <string.h>
#include <stdio.h>

#include "assets/asset.h"

#define NUM_X_BLOCKS 8
#define NUM_Y_BLOCKS 4
#define BLOCK_WIDTH 40
#define BLOCK_HEIGHT 8

#define BALL_LEN 8
#define PADDLE_LEN 8

#define X_VEL 2
#define Y_VEL 2
#define PADDLE_Y 232

uint16_t ball_x = 8;
uint16_t ball_y = 224;
uint16_t paddle_x = 0;
const uint8_t paddle_len = 64;

uint32_t gametime = 0;

bool blocks[NUM_Y_BLOCKS][NUM_X_BLOCKS];

enum direction {
    NONE, UP, DOWN, LEFT, RIGHT
};

int8_t x_vel = 1;
int8_t y_vel = -1;

void init();
void update(struct input, uint32_t);
void draw();

struct rom rom = {
    .init = init,
    .update = update,
    .draw = draw,
    .running = true,
};

void collide_block(uint16_t y, uint16_t x, int16_t tmp_y, int16_t tmp_x) {
    uint8_t block_x_index = tmp_x / BLOCK_WIDTH;
    uint8_t block_y_index = tmp_y / BLOCK_HEIGHT;
    if (tmp_y / BLOCK_HEIGHT > NUM_Y_BLOCKS)
        return;

    if (blocks[block_y_index][block_x_index]) {
        blocks[block_y_index][block_x_index] = false;
        uint16_t block_x = block_x_index * BLOCK_WIDTH;
        uint16_t block_y = block_y_index * BLOCK_HEIGHT;
        if (x > block_x + BLOCK_WIDTH || x < block_x) {
            x_vel *= -1;
        } else if (y < block_y || y + BLOCK_HEIGHT > block_y) {
            y_vel *= -1;
        }
    }
}

void init() {
    struct palette palette;
    memset(&palette, 255, sizeof(struct palette));
    set_palette(&palette, 0);
    load_tilemap(map); 
    for (int y = 0; y < NUM_Y_BLOCKS; y++) {
        for (int x = 0; x < NUM_X_BLOCKS; x++) {
            blocks[y][x] = true;
        }
    }
}

void update(struct input input, uint32_t time) {
    uint32_t deltatime = time - gametime;
    gametime = time;

    uint8_t colliding;
    enum direction colliding_direction;

	uint16_t next_paddle_x = paddle_x + input.x * 8;
	if (next_paddle_x >= 0 && next_paddle_x <= 320 - paddle_len) {
    	paddle_x = next_paddle_x;
	}

    int16_t tmp_x = ball_x + X_VEL * x_vel;
    int16_t tmp_y = ball_y + Y_VEL * y_vel;

    collide_block(ball_y, ball_x, tmp_y, tmp_x);

    // LOG("ball: x %d, y %d, xvel %d, yvel %d, pad %d", ball_x, ball_y, x_vel, y_vel, paddle_x);

    if (tmp_y > 240 - PADDLE_LEN - BALL_LEN) {
        if (tmp_x > paddle_x && tmp_x < paddle_x + paddle_len) {
            y_vel *= -1;
        } else {
            rom.running = false;
            LOG("exiting");
        }
    } else if (tmp_y < 0) {
        y_vel *= -1;
    } else {
        ball_y = tmp_y;
    }

    if (tmp_x < 0 || tmp_x > 320 - BALL_LEN) {
        x_vel *= -1;
    } else {
        ball_x = tmp_x;
    }
}

void draw() {
    for (int y = 0; y < NUM_Y_BLOCKS; y++) {
        for (int x = 0; x < NUM_X_BLOCKS; x++) {
            if (blocks[y][x]) {
                for (int i = 0; i < 5; i++) {
                    draw_sprite(0, y * BLOCK_HEIGHT, x * BLOCK_WIDTH + i * 8);
                }
            }
        }
    }

    draw_sprite(0, ball_y, ball_x); 
    for (int i = 0; i < 8; i++) {
        draw_sprite(0, PADDLE_Y, paddle_x + i * 8);
    }
}
