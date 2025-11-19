#include <graphics.h>
#include <stdio.h>

// define custom dark green because WinBGI doesn't have DARKGREEN
#define DARKGREEN COLOR(0,100,0)

// -------- CLOUD --------
void drawCloud(int x, int y) {
    setcolor(WHITE);
    setfillstyle(SOLID_FILL, WHITE);
    fillellipse(x,     y, 28, 22);
    fillellipse(x+25,  y-10, 30, 24);
    fillellipse(x+50,  y, 28, 22);
    fillellipse(x+18,  y+10, 26, 20);
}

// -------- BIRD --------
void drawBird(int x, int y) {
    setcolor(DARKGRAY);
    setlinestyle(SOLID_LINE, 0, 2);
    line(x-10, y, x, y-6);
    line(x, y-6, x+10, y);
}

// -------- MOUNTAINS --------
void drawMountains() {
    // changed from LIGHTGRAY to BROWN
    setcolor(BROWN);
    setfillstyle(SOLID_FILL, BROWN);

    int m1[] = {50,400, 200,200, 350,400};
    int m2[] = {250,400, 420,180, 600,400};
    int m3[] = {500,400, 700,220, 900,400};

    fillpoly(3, m1);
    fillpoly(3, m2);
    fillpoly(3, m3);

    // no snow caps
}

// -------- GREEN GROUND ONLY --------
void drawGround() {
    setcolor(GREEN);
    setfillstyle(SOLID_FILL, GREEN);
    bar(0, 400, getmaxx(), getmaxy());
}

// -------- SUN --------
void drawSun() {
    setcolor(YELLOW);
    setfillstyle(SOLID_FILL, YELLOW);
    fillellipse(850, 90, 40, 40);
}

// -------- PLANE --------
void drawPlane(int x, int y) {

    // body
    setcolor(LIGHTCYAN);
    setfillstyle(SOLID_FILL, LIGHTCYAN);
    bar(x, y-10, x+120, y+10);

    // nose
    int nose[] = {x+120, y-10, x+150, y, x+120, y+10};
    setcolor(LIGHTBLUE);
    setfillstyle(SOLID_FILL, LIGHTBLUE);
    fillpoly(3, nose);

    // tail
    int tail[] = {x, y-10, x-15, y-25, x, y-10,  x-5, y+10, x-20, y+25, x-5, y+10};
    setcolor(LIGHTBLUE);
    drawpoly(3, tail);
    line(x-5, y+10, x-20, y+25);
    line(x-20, y+25, x, y+10);

    // wing
    int wing[] = {x+40, y+10, x+10, y+35, x+75, y+35, x+100, y+10, x+40, y+10};
    setcolor(LIGHTGRAY);
    setfillstyle(SOLID_FILL, LIGHTGRAY);
    fillpoly(5, wing);

    // windows
    setcolor(BLACK);
    for (int i = 15; i <= 105; i += 18)
        fillellipse(x+i, y-3, 3, 3);

    // credits
    setbkcolor(BLUE);
    setcolor(WHITE);
    settextstyle(SANS_SERIF_FONT, HORIZ_DIR, 1);

    char credit[] = "Made by: Sara (55), Snehal (56), Rishita (59)";
    outtextxy(10, 10, credit);
}

int main() {

    initwindow(1000, 600, "Plane Animation", 50, 50);

    int planeX = -180, planeY = 350;
    int c1 = 60, c2 = 300, c3 = 650;
    int b1 = 180, b2 = 520;

    int page = 0;

    while (!kbhit()) {

        setbkcolor(BLUE);  
        setactivepage(page);
        setvisualpage(1 - page);
        cleardevice();

        // blue background
        setcolor(BLUE);
        setfillstyle(SOLID_FILL, BLUE);
        bar(0, 0, getmaxx(), getmaxy());

        drawSun();
        drawMountains();
        drawGround();

        drawCloud(c1, 120);
        drawCloud(c2, 90);
        drawCloud(c3, 150);

        drawBird(b1, 160);
        drawBird(b2, 180);

        drawPlane(planeX, planeY);

        // movement
        planeX += 4;

        if (planeY > 250) planeY -= 1;

        c1 += 2; c2 += 2; c3 += 2;
        b1 += 3; b2 += 3;

        int W = getmaxx();
        if (planeX > W + 200) planeX = -200;
        if (c1 > W + 80) c1 = -80;
        if (c2 > W + 80) c2 = -80;
        if (c3 > W + 80) c3 = -80;
        if (b1 > W + 20) b1 = -20;
        if (b2 > W + 20) b2 = -20;

        page = 1 - page;
        delay(16);
    }

    closegraph();
    return 0;
}