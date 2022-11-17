//
// Created by luria on 28/02/2022.
//

#include "Enemy.h"
#include <cmath>

Enemy::Enemy()
{
  vector2 = new Vector2(0.1, 0.1);
}

Enemy::~Enemy()
{

}
float Enemy::getEnemySpeed() const
{
  return enemy_speed;
}
int Enemy::quadraticCurve(float x)
{
  return (x*x);
}

