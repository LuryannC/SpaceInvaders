//
// Created by l2-augustocerv on 25/02/2022.
//

#ifndef SPACEINVADERSSFML_PLAYER_H
#define SPACEINVADERSSFML_PLAYER_H

#include "../GameObject.h"

class Player : public GameObject
{
  public:
    Player();
    ~Player();
    void moveRight();
    void moveLeft();
    void moveUp();
    void moveDown();

   private:
  float speed = 8.0;



};

#endif // SPACEINVADERSSFML_PLAYER_H
