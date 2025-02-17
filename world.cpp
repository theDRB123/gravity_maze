#pragma once
#include "include/raylib.h"
#include "include/raymath.h"
#include "shape.cpp"
#include "ball.cpp"
#include <vector>
#include <iostream>

using namespace std;

struct WorldParms
{
    Vector2 gravity = {0, 0.1};
    float rotValue = 0;
    float restitution = 0.5;
    float friction = 0.5;
    Vector2 pivot = {500, 500};
};

class World
{
public:
    World() {};

    vector<Shape> shapes;
    vector<Ball> balls;
    WorldParms parms;

    void addShape(Shape shape)
    {
        shapes.push_back(shape);
    }

    void addShapes(vector<Shape> shapes)
    {
        for (int i = 0; i < shapes.size(); i++)
        {
            this->shapes.push_back(shapes[i]);
        }
    }

    void addBall(Ball ball)
    {
        balls.push_back(ball);
    }

    void draw()
    {
        for (int i = 0; i < shapes.size(); i++)
        {
            shapes[i].draw();
        }
        for (int i = 0; i < balls.size(); i++)
        {
            balls[i].draw();
        }
    }

    void UpdateRotValue()
    {
        for (int i = 0; i < shapes.size(); i++)
        {
            shapes[i].UpdateRotValuePivot(parms.rotValue, parms.pivot);
        }
    }
};