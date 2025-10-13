#include "player.h"

Player::Player()
{
    _speed = 45.0f;
}

void Player::update()
{
    // Update player transform and camera
    _transform.updateVectors();
}
