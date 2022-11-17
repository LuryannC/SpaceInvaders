
#ifndef SPACEINVADERS_GAMEOBJECT_H
#define SPACEINVADERS_GAMEOBJECT_H

#include <SFML/Graphics.hpp>

class GameObject
{
 public:
  GameObject();
  ~GameObject();
  sf::Sprite* getSprite();
  bool initialiseSprite(sf::Texture &texture, std::string filename);
  bool collisionCheck(sf::Sprite* object_1, sf::Sprite* object_2);

  bool visibility = true;

 protected:
  sf::Sprite* sprite = nullptr;

 private:




};


#endif // SPACEINVADERS_GAMEOBJECT_H
