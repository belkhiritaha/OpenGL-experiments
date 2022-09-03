#include "player.hpp"


Player::Player()
{
    x = 0.0f;
    y = 0.0f;
    z = 2.0f;
    Keys[0] = 0;
    Keys[1] = 0;
    Keys[2] = 0;
    Keys[3] = 0;
}


Player::~Player()
{
}


void Player::Update()
{
    Move();
    View();
}


void Player::Move()
{
    // std::cout << "Keys: " << Keys[0] << " " << Keys[1] << " " << Keys[2] << " " << Keys[3] << std::endl;

    float x_increment = (Keys[3] - Keys[2]) * speed;
    float y_increment = (Keys[0] - Keys[1]) * speed;

    x += x_increment;
    z += y_increment;
}


void Player::View()
{
    //std::cout << "X: " << x << " Y: " << y << std::endl;
}


float Player::getTheta()
{
    return theta;
}


float Player::getPhi()
{
    return phi;
}


float Player::getAlpha()
{
    return alpha;
}