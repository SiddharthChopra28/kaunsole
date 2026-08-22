#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/spi.h"
#include "ili9341.h"
#include "gfx.h"
#include "../backend.h"
#include "../graphics.h"


#define PIN_SCK  6
#define PIN_MOSI 7
#define PIN_CS   2
#define PIN_RST  3
#define PIN_DC   4

void backend_init(){

    stdio_init_all();

	LCD_setPins(PIN_DC, PIN_CS, PIN_RST, PIN_SCK, PIN_MOSI);
	LCD_setSPIperiph(spi0);
	LCD_initDisplay();
	LCD_setRotation(1); // landscape: 320x240

	GFX_createFramebuf();

}

void backend_deinit(){
    // nothing needed here
}

void backend_render(uint8_t pixelbuf[Y_RESOLUTION][X_RESOLUTION], uint32_t *palette){
    for (int y = 0; y < Y_RESOLUTION; y++) {
        for (int x = 0; x < X_RESOLUTION; x++) {
            uint32_t color = palette[pixelbuf[y][x]];
            uint16_t rgb565 = ((color >> 8 & 0xf8) << 8) |
                              ((color >> 5 & 0xfc) << 3) |
                              (color >> 3 & 0x1f);
            GFX_drawPixel(x, y, rgb565);
        }
    }
    GFX_flush();
}

void backend_audio(const void *buffer, uint16_t length){
    //pass
}

uint32_t backend_time(){
    return to_ms_since_boot(get_absolute_time());
}

struct input input = {0};

struct input backend_input(){

    return input;

}

void backend_sleep(uint32_t ms) {
    sleep_ms(ms);
}
