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
    float radius;
    Ball(Vector2 position, Vector2 velocity, float radius) : position(position), velocity(velocity), radius(radius) {};
    void update()
    {
        position = Vector2Add(position, velocity);
    };
    void draw()
    {
        DrawCircleV(position, radius, RED);
    };

    void checkCollision(vector<Shape> shapes){
        for (int i = 0; i < shapes.size(); i++)
        {
            checkCollision(shapes[i]);
        }
    }
    void checkCollisionWall(){
        bool collided = false;
        if (position.x - radius < 0 || position.x + radius > GetScreenWidth())
        {
            collided = true;
            velocity.x *= -1;
        }
        if (position.y - radius < 0 || position.y + radius > GetScreenHeight())
        {
            collided = true;
            velocity.y *= -1;
        }
        if(collided){
            cout << "Collision" << endl;
        }
    }
    void checkCollision(Shape shape)
    {
        bool collided = false;
        for (int i = 0; i < shape.edges.size(); i++)
        {
            Edge edge = shape.edges[i];
            Vector2 diff = Vector2Subtract(position, edge.start);
            float distance = abs(Vector2DotProduct(diff, edge.normal));
            // check if the ball is within the edge
            bool withinEdge = Vector2DotProduct(Vector2Normalize(position - edge.end), Vector2Normalize(position - edge.start)) < 0;

            if (withinEdge && distance < radius)
            {
                collided = true;
                velocity = Vector2Reflect(velocity, edge.normal);
            }
        }
        if (collided)
        {
            cout << "Collided" << endl;
        }
    };
};
