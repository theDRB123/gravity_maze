#pragma once
#include "include/raylib.h"
#include "include/raymath.h"
#include <vector>
#include "ball.cpp"
#include "shape.cpp"
#include "world.cpp"

class Collision
{
private:
    World &world;

public:
    Collision(World &world) : world(world) {}
    void collision()
    {
        for (int i = 0; i < world.balls.size(); i++)
        {
            collision(world.balls[i]);
        }
    }
    void collision(Ball &ball)
    {
        resolveCollisionWithWalls(ball);
        for (int i = 0; i < world.shapes.size(); i++)
        {
            resolveCollision(ball, world.shapes[i]);
        }
    }
    void resolveCollision(Ball &ball, Shape shape)
    {
        for (Edge edge : shape.edges)
        {
            Vector2 pos = Vector2Add(ball.position, ball.velocity);
            Vector2 diff = Vector2Subtract(pos, edge.start);

            // bool onEdge = Vector2DotProduct(Vector2Subtract(pos, edge.start), diff) * Vector2DotProduct(Vector2Subtract(pos, edge.end), diff) < 0;
            bool onEdge = Vector2DotProduct(Vector2Normalize(pos - edge.end), Vector2Normalize(pos - edge.start)) < 0;
            float distance = abs(Vector2DotProduct(diff, edge.normal));
            if (distance < ball.radius && onEdge)
            {
                double diff_distance = ball.radius - distance;
                Vector2 closestPoint = Vector2Add(edge.start, Vector2Normalize(Vector2Subtract(edge.end, edge.start)) * Vector2DotProduct(diff, Vector2Normalize(Vector2Subtract(edge.end, edge.start))));
                Vector2 velocityPoint = edge.GetVelocityPoint(closestPoint);
                Vector2 normal = Vector2Normalize(edge.normal * Vector2DotProduct(ball.velocity, edge.normal));
                // in the reference frame of the edge
                Vector2 rel_velocity = Vector2Subtract(ball.velocity * world.parms.restitution, velocityPoint);
                Vector2 relected_velocity = Vector2Reflect(rel_velocity, normal);
                // changing the reference back to the world
                std::cout << diff_distance << std::endl;
                ball.velocity = Vector2Add(relected_velocity, velocityPoint) * (diff_distance > 10 ? 2 : 1);
                // eliminate all the components of velocity perpendicular to the edge and in direction opposite to normal
                if (Vector2DotProduct(ball.velocity, normal) > 0)
                {
                    ball.velocity = Vector2Subtract(ball.velocity, normal * Vector2DotProduct(ball.velocity, normal));
                }
            }
        }
    }
    void resolveCollisionWithWalls(Ball &ball)
    {
        if (ball.position.x - ball.radius < 0 || ball.position.x + ball.radius > GetScreenWidth())
        {
            ball.velocity.x *= -1 * world.parms.restitution;
        }
        if (ball.position.y - ball.radius < 0 || ball.position.y + ball.radius > GetScreenHeight())
        {
            ball.velocity.y *= -1 * world.parms.restitution;
        }
    }
};