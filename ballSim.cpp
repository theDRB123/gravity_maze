#include "include/raylib.h"
#include <cmath>
#include <vector>
#include "shape.cpp"
#include "ball.cpp"

int ballSim()
{
    InitWindow(800, 600, "Ball and Slanted Rectangle Collision");
    SetTargetFPS(240);

    Shape shape = Shape({{250, 250}, {350, 250}, {350, 350}, {250, 350}}, BLACK, 5);

    Shape shape2 = Shape({{150, 150}, {300, 150}, {300, 300}, {150, 300}}, BLACK, 5);

    Shape shape3 = Shape({{400, 400}, {500, 400}, {500, 500}, {400, 500}}, BLACK, 5);

    Shape shape4 = Shape({{100, 100}, {200, 100}, {200, 200}, {100, 200}}, BLACK, 5);

//make triangles and wedges

    Shape shape5 = Shape({{100, 100}, {200, 100}, {150, 200}}, BLACK, 5);
    

    vector<Shape> shapes = {shape, shape2, shape3, shape4};

    Ball ball = Ball({300, 100}, {1, 1}, 10);

    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(RAYWHITE);

        for (int i = 0; i < shapes.size(); i++)
        {
            shapes[i].draw();
        }
        ball.checkCollisionWall();
        ball.checkCollision(shapes);

        ball.update();
        ball.draw();

        EndDrawing();
    }

    CloseWindow();
    return 0;
}