#include <graphics.h>
#include <iostream>
#include <cmath> // For sin function

using namespace std;

// Function to draw a more natural-looking cloud using multiple ellipses
void drawCloud(int x, int y) {
    const int CLOUD_COLOR = WHITE;
    setcolor(CLOUD_COLOR);
    setfillstyle(SOLID_FILL, CLOUD_COLOR);

    // Group of overlapping circles/ellipses
    fillellipse(x, y, 30, 20); // Center
    fillellipse(x + 25, y + 5, 25, 15); // Right bottom
    fillellipse(x - 25, y + 5, 25, 15); // Left bottom
    fillellipse(x + 10, y - 10, 20, 20); // Top right
    fillellipse(x - 15, y - 8, 20, 15); // Top left
}

// Function to draw a sleek, modern jet airplane
void drawAirplane(int x, int y) {
    const int BODY_COLOR = 8; // DARKGRAY
    const int WINDOW_COLOR = CYAN;
    const int WING_COLOR = LIGHTGRAY;
    const int OUTLINE_COLOR = WHITE;

    setcolor(OUTLINE_COLOR);

    // --- 1. Sleek Fuselage (tapered shape) ---
    // Points define a jet body: 150 units long, 30 wide at center
    int fuselage_points[] = {
        x + 150, y,          // Nose tip (0)
        x + 130, y + 15,     // Top rear nose (1)
        x - 50, y + 15,      // Top rear body (2)
        x - 50, y - 15,      // Bottom rear body (3)
        x + 130, y - 15,     // Bottom rear nose (4)
        x + 150, y           // Close to nose tip (5)
    };
    setfillstyle(SOLID_FILL, BODY_COLOR);
    drawpoly(6, fuselage_points);
    fillpoly(6, fuselage_points);


    // --- 2. Swept Main Wing (right side, drawn as a filled polygon) ---
    int wing_points[] = {
        x + 40, y + 15,      // Root near body (1)
        x + 100, y + 70,     // Outer rear tip (2)
        x + 120, y + 60,     // Outer front tip (swept back) (3)
        x + 50, y + 5,       // Root near body (4)
        x + 40, y + 15       // Close the loop (5)
    };
    setfillstyle(SOLID_FILL, WING_COLOR);
    drawpoly(5, wing_points);
    fillpoly(5, wing_points);


    // --- 3. Vertical Tail Fin ---
    int tail_fin_points[] = {
        x - 45, y - 15,     // Base on body
        x - 20, y - 55,     // Top tip
        x - 5, y - 15,      // Rear base
        x - 45, y - 15
    };
    setfillstyle(SOLID_FILL, BODY_COLOR);
    drawpoly(4, tail_fin_points);
    fillpoly(4, tail_fin_points);

    // Horizontal Tail Stabilizer
    int stabilizer_points[] = {
        x - 50, y + 10,
        x - 70, y + 25,
        x - 70, y - 25,
        x - 50, y - 10
    };
    setfillstyle(SOLID_FILL, WING_COLOR);
    drawpoly(4, stabilizer_points);
    fillpoly(4, stabilizer_points);


    // --- 4. Windows (small circles for a cleaner look) ---
    setcolor(OUTLINE_COLOR);
    setfillstyle(SOLID_FILL, WINDOW_COLOR);
    
    // Cockpit/Pilot window
    circle(x + 135, y, 4); 
    floodfill(x + 135, y, OUTLINE_COLOR); 
    
    // Passenger windows
    circle(x + 100, y, 3); floodfill(x + 100, y, OUTLINE_COLOR);
    circle(x + 70, y, 3); floodfill(x + 70, y, OUTLINE_COLOR);
    circle(x + 40, y, 3); floodfill(x + 40, y, OUTLINE_COLOR);
}

int main() {
    int gd = DETECT, gm;
    initgraph(&gd, &gm, "");

    // The maximum x-coordinate plus some padding for the plane to leave the screen
    int max_x_exit = getmaxx() + 200;

    // Animate airplane across the screen
    for (int x_pos = -150; x_pos < max_x_exit; x_pos += 4) {
        cleardevice();

        // Sky background (LIGHTBLUE)
        setbkcolor(LIGHTBLUE);
        cleardevice();

        // Sun
        setcolor(YELLOW);
        setfillstyle(SOLID_FILL, YELLOW);
        circle(100, 80, 40);
        floodfill(100, 80, YELLOW);

        // Clouds (using improved function)
        drawCloud(200, 100);
        drawCloud(450, 70);
        drawCloud(680, 120);

        // Ground (A simpler ground line for aerial perspective)
        setcolor(GREEN);
        setfillstyle(SOLID_FILL, GREEN);
        rectangle(0, getmaxy() - 50, getmaxx(), getmaxy());
        floodfill(10, getmaxy() - 10, GREEN);

        // Calculate vertical oscillation using sine wave
        // This makes the plane gently bob up and down as it moves horizontally.
        // sin()