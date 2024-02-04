#include <iostream>
#include <fstream>
#include <bitset>
#include <vector>

#include "../vga16_graphics.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

typedef struct Pixel{
    uint8_t r;
    uint8_t g;
    uint8_t b;
}Pixel;

enum colors rgb_to_color_enum(int r, int g, int b) {
    if (r < 128 && g < 128 && b < 128) {
        return BLACK;
    } else if (r < 128 && g >= 128 && b < 128) {
        return DARK_GREEN;
    } else if (r < 128 && g >= 128 && b >= 128) {
        return MED_GREEN;
    } else if (r < 128 && g < 128 && b >= 128) {
        return GREEN;
    } else if (r < 128 && g < 128 && 128 <= b && b < 192) {
        return DARK_BLUE;
    } else if (r < 128 && g < 128 && b >= 192) {
        return BLUE;
    } else if (r < 128 && 128 <= g && g < 192 && b >= 192) {
        return LIGHT_BLUE;
    } else if (r < 128 && g >= 192 && b >= 192) {
        return CYAN;
    } else if (r >= 128 && g < 128 && b < 128) {
        return RED;
    } else if (r >= 128 && 128 <= g && g < 192 && b < 128) {
        return DARK_ORANGE;
    } else if (r >= 128 && 64 <= g && g < 192 && b < 128) {
        return ORANGE;
    } else if (r >= 128 && g >= 192 && b < 128) {
        return YELLOW;
    } else if (r >= 128 && g < 128 && 128 <= b && b < 192) {
        return MAGENTA;
    } else if (r >= 128 && g < 128 && b >= 192) {
        return PINK;
    } else if (r >= 128 && 128 <= g && g < 192 && b >= 192) {
        return LIGHT_PINK;
    } else {
        return WHITE;
    }
}

// Example usage
int main(int argc, char *argv[]){

    int width, height, channels;

    if(argc < 2){
        std::cout << "Please Provide BMP File" << std::endl;
        return 1;
    }

    uint8_t *image_data = stbi_load(argv[1], &width, &height, &channels, 0);
    
    if(!image_data){
        std::cout << "\nError Loading IMG\n" << std::endl;
        return 1;
    }

    std::vector<enum colors> bmp_pixels;
    for(int i = 0; i < (width*height)*3; i+=3){
        uint8_t r = image_data[i];
        uint8_t g = image_data[i+1];
        uint8_t b = image_data[i+2];
        bmp_pixels.push_back(rgb_to_color_enum(r, g, b));
    }

    FILE *out_file = fopen("output.vga", "w");

    if (out_file == NULL) {
        fprintf(stderr, "Error opening file.\n");
        return 1;  
    }
    fprintf(out_file, "%d\n", width);
    fprintf(out_file, "%d\n", height);
    for (int i = 0; i < bmp_pixels.size(); i++) {
        fprintf(out_file, "%d\n", bmp_pixels[i]);
    }

    fclose(out_file);
    stbi_image_free(image_data);
}