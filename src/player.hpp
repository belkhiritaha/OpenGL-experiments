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
        float x;
        float y;
        float z;
        int Keys[4];
        float speed = 0.1f;
};