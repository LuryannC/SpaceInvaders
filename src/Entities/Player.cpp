//
// Created by l2-augustocerv on 25/02/2022.
//

#include "Player.h"

Player::Player()
{

}
Player::~Player()
{

}

void Player::moveLeft()
{
  sprite->move(1 * speed, 0);
}

void Player::moveRight()
{
  sprite->move(-1 * speed, 0);
}

void Player::moveUp()
{
  sprite->move(0, -1 * speed);
}

void Player::moveDown()
{
  sprite->move(0, 1 * speed);
}

