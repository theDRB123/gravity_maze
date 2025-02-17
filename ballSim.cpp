#include "include/raylib.h"
#include <cmath>
#include <vector>
#include <map>
#include "shape.cpp"
#include "ball.cpp"
#include "world.cpp"
#include "control.cpp"
#include "physics.cpp"
// 10 pixels = 1 meter
// g = 9.8 m/s^2

map<int, Color> colors = {
    {0, RED},
    {1, GREEN},
    {2, BLUE},
    {3, YELLOW},
    {4, ORANGE},
    {5, PURPLE},
    {6, PINK},
    {7, BROWN},
    {8, MAROON},
    {9, DARKBLUE},
    {10, DARKGREEN},
    {11, DARKPURPLE},
    {12, DARKGRAY},
    {13, DARKBROWN},
};

int ballSim()
{
    InitWindow(1000, 1000, "Ball and Slanted Rectangle Collision");
    SetTargetFPS(120);

    vector<Shape> shapes = {
        Shape({{150, 150}, {850, 150}, {850, 850}, {150, 850}, {150, 150}}),
        Shape({{350, 600}, {350, 225}, {750, 225}, {750, 400}})};

    World world;


    for (int i = 0; i < 10; i++)
    {
        Ball ball = Ball({300.0f + i, 300}, {0, 0}, 40, colors[i % 13]);
        world.addBall(ball);
    }

    world.addShapes(shapes);
    world.UpdateRotValue();

    int counter = 0;

    bool controlFlag = false;
    Vector2 pos = {0, 0};

    Control control = Control(world);
    Physics physics = Physics(world);

    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(BLACK);

        control.control(controlFlag, pos);

        counter++;
        physics.applyGravity();
        physics.collision();
        physics.update();
        world.draw();

        EndDrawing();
    }

    CloseWindow();
    return 0;
}