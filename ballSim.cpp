#include "include/raylib.h"
#include <cmath>
#include <vector>
#include "shape.cpp"
#include "ball.cpp"
#include "world.cpp"

// 10 pixels = 1 meter
// g = 9.8 m/s^2

int ballSim()
{
    InitWindow(800, 800, "Ball and Slanted Rectangle Collision");
    SetTargetFPS(60);

    vector<Shape> shapes = {
        Shape({{0, 0},
               {50, 100},
               {100, 200},
               {150, 300},
               {200, 400},
               {250, 500},
               {300, 600},
               {350, 700},
               {400, 800},
               {0, 800},
               {0, 0}}),
    };

    Ball ball = Ball({300, 100}, {0, 0}, 10);

    World world;
    world.addBall(ball);
    world.addShapes(shapes);

    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(RAYWHITE);

        world.update();
        world.draw();

        EndDrawing();
    }

    CloseWindow();
    return 0;
}