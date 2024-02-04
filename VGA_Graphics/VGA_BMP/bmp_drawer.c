/**
 * Hunter Adams (vha3@cornell.edu)
 * 
 *
 * HARDWARE CONNECTIONS
   - GPIO 16 ---> VGA Hsync 
   - GPIO 17 ---> VGA Vsync 
   - GPIO 18 ---> VGA Green lo-bit --> 470 ohm resistor --> VGA_Green
   - GPIO 19 ---> VGA Green hi_bit --> 330 ohm resistor --> VGA_Green
   - GPIO 20 ---> 330 ohm resistor ---> VGA-Blue 
   - GPIO 21 ---> 330 ohm resistor ---> VGA-Red 
   - RP2040 GND ---> VGA-GND
 *
 * RESOURCES USED
 *  - PIO state machines 0, 1, and 2 on PIO instance 0
 *  - DMA channels obtained by claim mechanism
 *  - 153.6 kBytes of RAM (for pixel color data)
 *
 */

// VGA graphics library
#include "vga16_graphics.h"
#include <stdio.h>
#include <stdlib.h>
#include "pico/stdlib.h"
#include "hardware/pio.h"
#include "hardware/dma.h"

// Some globals for storing timer information
volatile unsigned int time_accum = 0;
unsigned int time_accum_old = 0 ;
char timetext[40];

// Timer interrupt
bool repeating_timer_callback(struct repeating_timer *t) {

    time_accum += 1 ;
    return true;
}

void drawIMG(FILE* file,int start_x, int start_y){
    int width,height;
    int color;
    fscanf (file, "%d", &width);
    fscanf (file, "%d", &height);
    for(int y =start_y; y < start_y+height; y++){
        for(int x = start_x; x < start_x+width; x++){
            fscanf (file, "%d", &color);
            drawPixel(x,y,color);
        }
    }
    fscanf (file, "%d", &color);
}

int main() {


    FILE *vga_data = fopen("santa.vga","r");

    //Initialize stdio
    stdio_init_all();

    // Initialize the VGA screen
    initVGA() ;

    // color chooser
    char color_index = 0 ;

    // position of the disc primitive
    short disc_x = 0 ;
    // position of the box primitive
    short box_x = 0 ;
    // position of vertical line primitive
    short Vline_x = 350;
    // position of horizontal line primitive
    short Hline_y = 250;

    // Draw some filled rectangles
    fillRect(64, 0, 176, 50, BLUE); // blue box
    fillRect(250, 0, 176, 50, RED); // red box
    fillRect(435, 0, 176, 50, GREEN); // green box

    // Write some text
    setTextColor(WHITE) ;
    setCursor(65, 0) ;
    setTextSize(1) ;
    writeString("Raspberry Pi Pico") ;
    setCursor(65, 10) ;
    writeString("Graphics primitives demo") ;
    setCursor(65, 20) ;
    writeString("Noah Breedy") ;
    setCursor(65, 30) ;
    writeString("teenyAT@sunypoly.edu") ;
   
    // Setup a 1Hz timer
    struct repeating_timer timer;
    add_repeating_timer_ms(-1000, repeating_timer_callback, NULL, &timer);
    drawIMG(vga_data,0, 0);


    while(1) {
        // Timing text
        if (time_accum != time_accum_old) {
            time_accum_old = time_accum ;
            fillRect(250, 20, 176, 30, RED); // red box
            sprintf(timetext, "%d", time_accum) ;
            setCursor(250, 20) ;
            setTextSize(2) ;
            writeString(timetext) ;
        }

        // A brief nap
        sleep_ms(10) ;

   }
    fclose(vga_data);
    return 0;
}
