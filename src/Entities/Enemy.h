//
// Created by luria on 28/02/2022.
//

#ifndef SPACEINVADERSSFML_ENEMY_H
#define SPACEINVADERSSFML_ENEMY_H

#include "../GameObject.h"
#include "../Vector2.h"

class Enemy : public GameObject
{
 public:
  Enemy();
  ~Enemy();


  int quadraticCurve(float x);
  Vector2* vector2;

  float getEnemySpeed() const;

 private:
  float enemy_speed = 2.0;
};

#endif // SPACEINVADERSSFML_ENEMY_H
