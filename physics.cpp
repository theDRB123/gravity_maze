#pragma once
#include "include/raylib.h"
#include "include/raymath.h"
#include <vector>
#include "ball.cpp"
#include "shape.cpp"
#include "world.cpp"

class Physics
{
private:
    World &world;

public:
    Physics(World &world) : world(world) {}
    void collision()
    {
        for (int i = 0; i < world.balls.size(); i++)
        {
            collision(world.balls[i]);
        }
    }
    void update()
    {
        for (Shape &shape : world.shapes)
        {
            shape.update();
        }
        for (int i = 0; i < world.balls.size(); i++)
        {
            world.balls[i].update();
        }
    }
    void applyGravity()
    {
        for (int i = 0; i < world.balls.size(); i++)
        {
            world.balls[i].velocity = Vector2Add(world.balls[i].velocity, world.parms.gravity);
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

            bool onEdge = Vector2DotProduct(Vector2Normalize(pos - edge.end), Vector2Normalize(pos - edge.start)) < 0;
            pair<bool, bool> onEdgeTip = (Vector2Distance(pos, edge.start) < ball.radius)
                                             ? make_pair(true, true)
                                         : (Vector2Distance(pos, edge.end) < ball.radius)
                                             ? make_pair(true, false)
                                             : make_pair(false, false);
            float distance = abs(Vector2DotProduct(diff, edge.normal));
            if (distance < ball.radius && onEdge)
            {
                double diff_distance = ball.radius - distance;
                Vector2 closestPoint = Vector2Add(edge.start, Vector2Normalize(Vector2Subtract(edge.end, edge.start)) * Vector2DotProduct(diff, Vector2Normalize(Vector2Subtract(edge.end, edge.start))));
                Vector2 velocityPoint = edge.GetVelocityPoint(closestPoint);
                Vector2 normal = Vector2Normalize(edge.normal * Vector2DotProduct(ball.velocity, edge.normal));
                Vector2 rel_velocity = Vector2Subtract(ball.velocity * world.parms.restitution, velocityPoint);
                Vector2 relected_velocity = Vector2Reflect(rel_velocity, normal);
                Vector2 diff_distance_velocity = normal * log(1 + diff_distance);
                ball.velocity = relected_velocity + velocityPoint - diff_distance_velocity;
                if (Vector2DotProduct(ball.velocity, normal) > 0)
                {
                    ball.velocity = Vector2Subtract(ball.velocity, normal * Vector2DotProduct(ball.velocity, normal));
                }
            }
            else if (onEdgeTip.first)
            {
                Vector2 velocityPoint;
                Vector2 diff;
                if (onEdgeTip.second)
                {
                    velocityPoint = edge.GetVelocityPoint(edge.start);
                    diff = Vector2Normalize(Vector2Subtract(edge.start, pos));
                }
                else
                {
                    velocityPoint = edge.GetVelocityPoint(edge.end);
                    diff = Vector2Normalize(Vector2Subtract(edge.end, pos));
                }
                Vector2 rel_velocity = Vector2Subtract(ball.velocity, velocityPoint);
                Vector2 diff_velocity = diff * Vector2DotProduct(rel_velocity, diff);
                Vector2 reflected_velocity = rel_velocity - diff_velocity * 2;
                ball.velocity = Vector2Add(reflected_velocity, velocityPoint);
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