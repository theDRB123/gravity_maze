#include "include/raylib.h"
#include "include/raymath.h"
#include <vector>
#pragma once
using namespace std;


struct Edge
{
    Vector2 start;
    Vector2 end;
    Vector2 normal;
    Edge(Vector2 start, Vector2 end) : start(start), end(end)
    {
        Vector2 diff = Vector2Subtract(end, start);
        normal = Vector2Normalize(Vector2Rotate(diff, -PI/2));
    };
    void DrawNormal(){
        Vector2 mid = Vector2Add(start, end) / 2;
        DrawCircleV(mid, 5, RED);
        DrawCircleV(Vector2Add(mid, normal * 50), 5, RED);
        DrawLineEx(mid, Vector2Add(mid, normal * 50), 5, RED);
    }
};



class Shape
{
public:
    Shape(vector<Vector2> vertices) : vertices(vertices) { createEdges(); };
    Shape(vector<Vector2> vertices, Color color) : vertices(vertices), color(color) { createEdges(); };
    Shape(vector<Vector2> vertices, Color color, float thickness) : vertices(vertices), color(color), thickness(thickness) { createEdges(); };
    Shape() {};

    vector<Vector2> vertices;
    vector<Edge> edges;
    Color color = BLACK;
    float thickness = 10.0f;

    void createEdges() {
        for (int i = 0; i < vertices.size(); i++) {
            edges.emplace_back(vertices[i], vertices[(i + 1) % vertices.size()]);
        }
    }

    void draw()
    {
        for (int i = 0; i < vertices.size(); i++)
        {
            DrawLineEx(vertices[i], vertices[(i + 1) % vertices.size()], thickness, color);
        }
    };

    void drawNormals()
    {
        for (int i = 0; i < vertices.size(); i++)
        {
            edges[i].DrawNormal();
        }
    };
};
