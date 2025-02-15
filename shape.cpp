#include "include/raylib.h"
#include "include/raymath.h"
#include <vector>
#pragma once
using namespace std;

Vector2 VectorRotate(Vector2 v, float angle, Vector2 pivot = {0, 0})
{
    Vector2 diff = Vector2Subtract(v, pivot);
    Vector2 rotated = Vector2Add(pivot, Vector2Rotate(diff, angle));
    return rotated;
}

struct Edge
{
    Vector2 start;
    Vector2 end;
    Vector2 normal;

    Vector2 vEnd;
    Vector2 vStart;

    float rotValue = 0;
    Vector2 pivot = {0, 0};

    Edge(Vector2 start, Vector2 end) : start(start), end(end)
    {
        UpdateNormal();
    };
    void UpdateNormal()
    {
        normal = Vector2Normalize(Vector2Rotate(Vector2Subtract(end, start), -PI / 2));
    };
    void UpdateRotValuePivot(float rotValue, Vector2 pivot)
    {
        this->rotValue = rotValue;
        this->pivot = pivot;
    };
    void Update()
    {
        start = VectorRotate(start, rotValue, pivot);
        end = VectorRotate(end, rotValue, pivot);

        vStart = Vector2Rotate(Vector2Subtract(start, pivot), PI / 2) * rotValue;
        vEnd = Vector2Rotate(Vector2Subtract(end, pivot), PI / 2) * rotValue;

        UpdateNormal();
    };
    void DrawNormal()
    {
        Vector2 mid = Vector2Add(start, end) / 2;
        DrawCircleV(mid, 5, RED);
        DrawCircleV(Vector2Add(mid, normal * 50), 5, RED);
        DrawLineEx(mid, Vector2Add(mid, normal * 50), 5, RED);
    };
    void Draw()
    {
        DrawLineEx(start, end, 5, RAYWHITE);
    };
    Vector2 GetVelocityPoint(Vector2 point)
    {
        float length = Vector2Distance(start, end);
        return Vector2Add(vStart * (Vector2Distance(point, end) ), vEnd * (Vector2Distance(point, start) )) / length;
    };
    void DrawVelocities()
    {
        DrawLineEx(start, Vector2Add(start, vStart * 10), 5, RED);

        for (int i = 0; i < 10; i++)
        {
            Vector2 point = Vector2Lerp(start, end, i / 10.0);
            DrawLineEx(point, Vector2Add(point, GetVelocityPoint(point) * 10), 5, RED);
        }

        DrawLineEx(end, Vector2Add(end, vEnd * 10), 5, RED);
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
    Color color = RAYWHITE;
    float thickness = 10.0f;

    void createEdges()
    {
        for (int i = 0; i < vertices.size(); i++)
        {
            edges.emplace_back(vertices[i], vertices[(i + 1) % vertices.size()]);
        }
    }

    void draw()
    {
        for (int i = 0; i < edges.size(); i++)
        {
            edges[i].Draw();
            // edges[i].DrawNormal();
            edges[i].DrawVelocities();
        }
    };

    void drawNormals()
    {
        for (int i = 0; i < vertices.size(); i++)
        {
            edges[i].DrawNormal();
        }
    };

    void Update()
    {
        for (int i = 0; i < edges.size(); i++)
        {
            edges[i].Update();
        }
    }

    void UpdateRotValuePivot(float rotValue, Vector2 pivot)
    {
        for (int i = 0; i < edges.size(); i++)
        {
            edges[i].UpdateRotValuePivot(rotValue, pivot);
        }
    }
};
