
#include "GameObject.h"
#include "iostream"

GameObject::GameObject()
{
  sprite = new sf::Sprite;
}

GameObject::~GameObject()
{

}

bool GameObject::initialiseSprite(sf::Texture& texture, std::string filename)
{
  if (!texture.loadFromFile(filename)){
    std::cout << "Failed to load: " + filename << std::endl;
    return false;
  }
  sprite->setTexture(texture);
  return true;
}

sf::Sprite* GameObject::getSprite()
{
  return sprite;
}


bool GameObject::collisionCheck(sf::Sprite* object_1, sf::Sprite* object_2)
{
  float object_1_tl_x = object_1->getPosition().x;
  float object_1_tl_y = object_1->getPosition().y;
  float object_1_br_x = object_1->getPosition().x + object_1->getGlobalBounds().width;
  float object_1_br_y = object_1->getPosition().y + object_1->getGlobalBounds().height;


  float object_2_tl_x = object_2->getPosition().x;
  float object_2_tl_y = object_2->getPosition().y;
  float object_2_br_x = object_2->getPosition().x + object_2->getGlobalBounds().width;
  float object_2_br_y = object_2->getPosition().y + object_2->getGlobalBounds().height;


  if (object_1_br_x > object_2_tl_x &&
      object_1_tl_x < object_2_br_x &&
      object_1_br_y > object_2_tl_y &&
      object_1_tl_y < object_2_br_y)
  {
    return true;
  }
  return false;
}

