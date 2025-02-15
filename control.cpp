#pragma once
#include "include/raylib.h"
#include "include/raymath.h"

#include "shape.cpp"
#include "ball.cpp"
#include "world.cpp"
#include <vector>

class Control
{
private:
    World &world;

public:
    Control(World& world) : world(world) {};
    void control(bool &controlFlag, Vector2 &pos)
    {
        if (IsMouseButtonDown(MOUSE_LEFT_BUTTON) && controlFlag)
        {
            Vector2 cPos = GetMousePosition();

            Vector2 dcPos = Vector2Normalize(Vector2Subtract(cPos, world.parms.pivot));
            Vector2 dPos = Vector2Normalize(Vector2Subtract(pos, world.parms.pivot));

            float dotProduct = Vector2DotProduct(dcPos, dPos);

            Vector3 pos3 = {dPos.x, dPos.y, 0};
            Vector3 cpos3 = {dcPos.x, dcPos.y, 0};

            float diff = Vector3CrossProduct(pos3, cpos3).z < 0 ? -1 : 1;

            world.parms.rotValue = (1 - dotProduct) * diff * 0.01;
            world.UpdateRotValue();
            pos = VectorRotate(pos, world.parms.rotValue, world.parms.pivot);
        }
        if (IsMouseButtonDown(MOUSE_LEFT_BUTTON) && !controlFlag)
        {
            pos = GetMousePosition();
            controlFlag = true;
        }
        if (IsMouseButtonReleased(MOUSE_LEFT_BUTTON) && controlFlag)
        {
            world.parms.rotValue = 0;
            world.UpdateRotValue();
            controlFlag = false;
        }
    };
};