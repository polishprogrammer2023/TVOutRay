#ifndef TVOUTRAY
#define TVOUTRAY
#include "raylib.h"
#include <stdint.h>
#include <stdlib.h> // dla abs()

// macros for readability when selecting mode.
#define PAL 1
#define NTSC 0
#define _PAL 1
#define _NTSC 0



typedef struct {
    int dummy;
    uint8_t scale;    // nowa zmienna skali
} TVOut;
void TVOut_begin(TVOut* self, uint8_t mode, uint8_t x, uint8_t y);
// rysuje pojedynczy piksel powiększony 4x
static inline void sp(TVOut* self, int x, int y, char c) {
    Color color;
    if (c == 1) color = WHITE;
    else if (c == 0) color = BLACK;
    else color = GRAY; // np. dla flip / toggle

    DrawRectangle(x * self->scale, y * self->scale, self->scale, self->scale, color);
}
void TVOut_draw_line(TVOut* self, int x0, int y0, int x1, int y1, char c);
// zmiana skali w trakcie działania
void TVOut_set_scale(TVOut* self, uint8_t scale);
void TVOut_bitmap(TVOut* self, uint8_t x, uint8_t y, const unsigned char* bmp, uint8_t width, uint8_t lines);

#endif