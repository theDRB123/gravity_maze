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
    SetTargetFPS(120);

    // vector<Shape> shapes = {
    //     Shape({{0, 0},
    //            {50, 100},
    //            {100, 200},
    //            {150, 300},
    //            {200, 400},
    //            {250, 500},
    //            {300, 600},
    //            {350, 700},
    //            {400, 800},
    //            {0, 800},
    //            {0, 0}}),
    // };

    vector<Shape> shapes = {
        Shape({{50, 50}, {750, 50}, {750, 750}, {50, 750}}),
        Shape({{380, 100}, {420, 100}, {420, 700}, {380, 700}})
    };



    World world;

    
    Ball ball = Ball({300, 300}, {0, 0}, 20);
    // Ball ball2 = Ball({400, 300}, {0, 0}, 20);
    // Ball ball3 = Ball({500, 300}, {0, 0}, 20);
    // Ball ball4 = Ball({600, 300}, {0, 0}, 20);
    // Ball ball5 = Ball({700, 300}, {0, 0}, 20);
    // Ball ball6 = Ball({800, 300}, {0, 0}, 20);
    // Ball ball7 = Ball({900, 300}, {0, 0}, 20);
    // Ball ball8 = Ball({1000, 300}, {0, 0}, 20);




    world.addBall(ball);
    // world.addBall(ball2);
    // world.addBall(ball3);
    // world.addBall(ball4);
    // world.addBall(ball5);
    // world.addBall(ball6);
    // world.addBall(ball7);
    // world.addBall(ball8);
    

    world.addShapes(shapes);

    world.UpdateRotValue();

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