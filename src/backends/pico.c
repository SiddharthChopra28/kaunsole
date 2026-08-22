#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware_adc/spi.h"
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
    uint32_t framebuffer[Y_RESOLUTION][X_RESOLUTION];
    for (int y = 0; y < Y_RESOLUTION; y++) {
        for (int x = 0; x < X_RESOLUTION; x++) {
            GFX_drawPixel(x,y, pallete[pixelbuf[y][x]]);
        }
    }


}

void backend_audio(const void *buffer, uint16_t length){
    //pass
}

uint32_t backend_time(){
    return uint32_t(to_ms_since_boot(get_absolute_time()));
}

struct input = {0};

struct input backend_input(){

    return input;

}