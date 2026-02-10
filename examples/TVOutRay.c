#include "TVOutRay.h"
#include "raylib.h"
#include <stdint.h>
#include <stdlib.h>

void TVOut_begin(TVOut* self, uint8_t mode, uint8_t x, uint8_t y) {
    if (self->scale == 0){
        self->scale = 4;
    }
	if(mode == PAL){
        InitWindow(x*self->scale, y*self->scale, "TVOut PAL program for Raylib");
        SetTargetFPS(50);
    }
    if(mode == NTSC){
        InitWindow(x*self->scale, y*self->scale, "TVOut NTSC program for Raylib");
        SetTargetFPS(60);
    }
}

void TVOut_draw_line(TVOut* self, int x0, int y0, int x1, int y1, char c) {
    int dx = x1 - x0;
    int dy = y1 - y0;
    int s1 = (dx >= 0) ? 1 : -1;
    int s2 = (dy >= 0) ? 1 : -1;

    dx = abs(dx);
    dy = abs(dy);

    int xchange = 0;
    if (dy > dx) {
        int temp = dx;
        dx = dy;
        dy = temp;
        xchange = 1;
    }

    int e = (dy << 1) - dx;
    int x = x0;
    int y = y0;

    for (int j = 0; j <= dx; j++) {
        sp(self, x, y, c);

        if (e >= 0) {
            if (xchange)
                x += s1;
            else
                y += s2;
            e -= (dx << 1);
        }

        if (xchange)
            y += s2;
        else
            x += s1;

        e += (dy << 1);
    }
}

void TVOut_set_scale(TVOut* self, uint8_t scale) {
    self->scale = scale;
}

void TVOut_bitmap(TVOut* self, uint8_t x, uint8_t y, const unsigned char* bmp,
                  uint8_t width, uint8_t lines)
{
    uint16_t idx = 0;

    if(width == 0) width = bmp[idx++];
    if(lines == 0) lines = bmp[idx++];

    uint8_t bytes_per_row = (width + 7) / 8; // ile bajtów na wiersz

    for(uint8_t row = 0; row < lines; row++) {
        for(uint8_t b = 0; b < bytes_per_row; b++) {
            unsigned char byte = bmp[idx++];
            for(uint8_t bit = 0; bit < 8; bit++) {
                uint8_t px = b*8 + bit;
                if(px >= width) break;
                char c = (byte & (0x80 >> bit)) ? 1 : 0;
                sp(self, x + px, y + row, c);
            }
        }
    }
}