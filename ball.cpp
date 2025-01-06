#pragma once
#include "include/raylib.h"
#include "include/raymath.h"
#include "shape.cpp"
#include <vector>
#include <iostream>
using namespace std;



struct Ball
{
    Vector2 position;
    Vector2 velocity;
    Color color = RED;
    float radius;
    Ball(Vector2 position, Vector2 velocity, float radius) : position(position), velocity(velocity), radius(radius) {};
    Ball(Vector2 position, Vector2 velocity, float radius, Color color) : position(position), velocity(velocity), radius(radius), color(color) {};
    void update()
    {
        position = Vector2Add(position, velocity);
    }

    void draw()
    {
        DrawCircleV(position, radius, color);
    }

    void checkCollision(vector<Shape> shapes, float restitution){
        for (int i = 0; i < shapes.size(); i++)
        {
            checkCollision(shapes[i], restitution);
        }
    }

    void checkCollisionWall(float restitution){
        bool collided = false;
        if (position.x - radius < 0 || position.x + radius > GetScreenWidth())
        {
            collided = true;
            velocity.x *= -1 * restitution;
        }
        if (position.y - radius < 0 || position.y + radius > GetScreenHeight())
        {
            collided = true;
            velocity.y *= -1 * restitution;
        }
        if(collided){
            cout << "Collision" << endl;
        }
    }

    void checkCollision(Shape shape, float restitution)
    {
        bool collided = false;
        for (int i = 0; i < shape.edges.size(); i++)
        {
            Edge edge = shape.edges[i];
            Vector2 next_pos = Vector2Add(position, velocity);
            Vector2 diff = Vector2Subtract(next_pos, edge.start);

            float distance = abs(Vector2DotProduct(diff, edge.normal));
            bool withinEdge = Vector2DotProduct(Vector2Normalize(next_pos - edge.end), Vector2Normalize(next_pos- edge.start)) < 0;
            
            Vector2 closestPoint = Vector2Add(edge.start, Vector2Normalize(Vector2Subtract(edge.end, edge.start)) * Vector2DotProduct(diff, Vector2Normalize(Vector2Subtract(edge.end, edge.start))));

            Vector2 velocityPoint = edge.GetVelocityPoint(closestPoint);


            if (withinEdge && distance < radius)
            {
                collided = true;
                // velocity = Vector2Reflect(velocity, edge.normal) * restitution;
                velocity = Vector2Add(Vector2Reflect(Vector2Subtract(velocity, velocityPoint), edge.normal), velocityPoint) * restitution;
            }
        }
        if (collided)
        {
            cout << "Collided" << endl;
        }
    };
};
