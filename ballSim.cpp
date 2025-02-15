#include "include/raylib.h"
#include <cmath>
#include <vector>
#include <map>
#include "shape.cpp"
#include "ball.cpp"
#include "world.cpp"
#include "control.cpp"
#include "collision.cpp"
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
    InitWindow(800, 800, "Ball and Slanted Rectangle Collision");
    SetTargetFPS(120);

    vector<Shape> shapes = {
        Shape({{50, 50}, {750, 50}, {750, 750}, {50, 750}}),
        Shape({{380, 100}, {420, 100}, {420, 700}, {380, 700}})};

    World world;


    for (int i = 0; i < 10; i++)
    {
        Ball ball = Ball({300.0f + i, 300}, {0, 0}, 20, colors[i % 13]);
        world.addBall(ball);
    }

    world.addShapes(shapes);
    world.UpdateRotValue();

    int counter = 0;

    bool controlFlag = false;
    Vector2 pos = {0, 0};

    Control control = Control(world);
    Collision collisionController = Collision(world);

    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(BLACK);

        control.control(controlFlag, pos);

        counter++;
        world.applyGravity();
        collisionController.collision();
        world.update();
        world.draw();

        EndDrawing();
    }

    CloseWindow();
    return 0;
}