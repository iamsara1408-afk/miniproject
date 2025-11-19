#include <graphics.h>
#include <iostream>
#include <cmath>
#include <math.h>   // For sin and cos functions
#include <stdlib.h> // Standard library for general compatibility

using namespace std;

// Draw a cloud
void drawCloud(int x, int y) {
    setcolor(WHITE);
    setfillstyle(SOLID_FILL, WHITE);
    
    // Cloud shape using multiple circles
    circle(x, y, 20);
    circle(x + 20, y + 10, 25);
    circle(x - 20, y + 10, 25);
    
    // Fill the circles
    floodfill(x, y, WHITE);
    floodfill(x + 20, y + 10, WHITE);
    floodfill(x - 20, y + 10, WHITE);
}

// Draw a tilted airplane
void drawAirplane(int x, int y, float angle) {
    setcolor(WHITE);
    setfillstyle(SOLID_FILL, LIGHTGRAY); // LIGHTGRAY constant requires graphics.h

    // Convert angle from degrees to radians for math functions
    float rad = angle * 3.14159 / 180.0;

    // -----------------------------------------------------------------
    // FIX: Using C preprocessor macros to define rotation logic (universal compatibility)
    // This replaces the problematic C++11 lambdas and avoids syntax errors.
    // ROTATE_X(px, py): Rotates point (px, py) around (x, y) by 'rad'
    // -----------------------------------------------------------------
    #define ROTATE_X(px, py) (x + (int)(px * cos(rad) - py * sin(rad)))
    #define ROTATE_Y(px, py) (y + (int)(px * sin(rad) + py * cos(rad)))

    // Draw body (Rectangle)
    int body[] = {
        ROTATE_X(0, 0), ROTATE_Y(0, 0),
        ROTATE_X(100, 0), ROTATE_Y(100, 0),
        ROTATE_X(100, 20), ROTATE_Y(100, 20),
        ROTATE_X(0, 20), ROTATE_Y(0, 20)
    };
    fillpoly(4, body);

    // Nose (Triangle)
    int nose[] = {
        ROTATE_X(100, 0), ROTATE_Y(100, 0),
        ROTATE_X(120, 10), ROTATE_Y(120, 10),
        ROTATE_X(100, 20), ROTATE_Y(100, 20)
    };
    fillpoly(3, nose);

    // Tail (Triangle)
    int tail[] = {
        ROTATE_X(0, 5), ROTATE_Y(0, 5),
        ROTATE_X(-20, 15), ROTATE_Y(-20, 15),
        ROTATE_X(-20, 5), ROTATE_Y(-20, 5)
    };
    fillpoly(3, tail);

    // Top wing (Polygon)
    int topWing[] = {
        ROTATE_X(40, 0), ROTATE_Y(40, 0),
        ROTATE_X(80, -20), ROTATE_Y(80, -20),
        ROTATE_X(85, -10), ROTATE_Y(85, -10),
        ROTATE_X(45, 0), ROTATE_Y(45, 0)
    };
    fillpoly(4, topWing);

    // Bottom wing (Polygon)
    int bottomWing[] = {
        ROTATE_X(40, 20), ROTATE_Y(40, 20),
        ROTATE_X(80, 40), ROTATE_Y(80, 40),
        ROTATE_X(85, 30), ROTATE_Y(85, 30),
        ROTATE_X(45, 20), ROTATE_Y(45, 20)
    };
    fillpoly(4, bottomWing);

    // Windows (Ellipses)
    setfillstyle(SOLID_FILL, CYAN);
    for (int i = 0; i < 3; i++) {
        int wx = ROTATE_X(25 + i * 25, 8);
        int wy = ROTATE_Y(25 + i * 25, 8);
        fillellipse(wx, wy, 5, 5);
    }
    
    // Clean up the macros to avoid conflicts with other code
    #undef ROTATE_X
    #undef ROTATE_Y
}

// Draw background
void drawBackground() {
    setbkcolor(LIGHTBLUE);
    cleardevice();

    // Sun
    setcolor(YELLOW);
    setfillstyle(SOLID_FILL, YELLOW);
    fillellipse(100, 80, 40, 40);

    // Clouds
    drawCloud(200, 100);
    drawCloud(400, 70);
    drawCloud(600, 120);

    // Ground
    setcolor(GREEN);
    setfillstyle(SOLID_FILL, GREEN);
    rectangle(0, getmaxy() - 50, getmaxx(), getmaxy());
    floodfill(10, getmaxy() - 10, GREEN);
}

int main() {
    int gd = DETECT, gm;
    // The initgraph function sets up the graphics mode
    initgraph(&gd, &gm, nullptr); 

    int max_x = getmaxx();
    int page = 0;

    // Animate using page flipping for smooth movement
    for (int x = -150; x < max_x + 200; x += 5) {
        // Smooth upward tilt: angle oscillates slightly
        float angle = sin(x / 100.0) * 8; // gentle oscillation (-8° to +8°)
        int y = 250 - (x / 15);            // slow upward climb

        setactivepage(page);        // Draw on the hidden page
        cleardevice();              // Clear the active (hidden) page

        drawBackground();
        drawAirplane(x, y, angle);

        setvisualpage(page);        // Display the page we just drew
        delay(30);                  // Wait for 30 milliseconds
        page = 1 - page;            // Switch drawing to the other page
    }

    cout << "Press Enter to exit...";
    cin.get();
    closegraph();
    return 0;
}