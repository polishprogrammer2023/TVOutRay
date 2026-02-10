#include "TVOutRay.h"
#include "schematic.h"
#include "TVOlogo.h"


TVOut TV;

void intro(TVOut* TV, const unsigned char* TVOlogo);

int main(void)
{
    // Initialization
    
    TVOut_set_scale(&TV, 8);
    TVOut_begin(&TV, PAL, 120, 96);
    BeginDrawing();
    ClearBackground(BLACK);
    intro(&TV, TVOlogo);
    EndDrawing();


    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();
        ClearBackground(BLACK);
        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}


void intro(TVOut* TV, const unsigned char* TVOlogo) {
    uint8_t w = TVOlogo[0];
    uint8_t l = TVOlogo[1];
    uint8_t wb = (w + 7) / 8;
    for(uint8_t line = 1; line <= l; line++) {
        BeginDrawing();
        ClearBackground(BLACK);
        int index = wb * (l - line) + 2;
        TVOut_bitmap(TV, (120 - w) / 2, 0, &TVOlogo[index], w, line);

        EndDrawing();
        WaitTime(0.05f);  // pause between frames
    }

    for(uint8_t y = 0; y < (96 - l) / 2; y++) {
        BeginDrawing();
        ClearBackground(BLACK);
        TVOut_bitmap(TV, (120 - w) / 2, y, TVOlogo, 0, 0);  // drawing whole bitmap
        EndDrawing();
        WaitTime(0.05f);
    }

    // 3 second pause after intro
    WaitTime(3.0f);
    BeginDrawing();
    ClearBackground(BLACK);
    
}
