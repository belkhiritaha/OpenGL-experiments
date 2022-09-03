#pragma once
#include <iostream>
#include <vector>

class Player
{
    public:
        Player();
        ~Player();
        void Update();
        void Move();
        void View();
        float getTheta();
        float getPhi();
        float getAlpha();
        float x;
        float y;
        float z;
        float theta;
        float phi;
        float alpha;
        int Keys[4];
        float speed = 0.1f;
};