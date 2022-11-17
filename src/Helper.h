//
// Created by l2-augustocerv on 21/02/2022.
//

#ifndef SPACEINVADERSSFML_HELPER_H
#define SPACEINVADERSSFML_HELPER_H

#include "Entities/Player.h"
#include "Entities/Enemy.h"
#include "GameObject.h"
#include "Vector2.h"
#include <SFML/Graphics.hpp>

class Helper
{
  public:
   Helper(sf::RenderWindow& window);
   ~Helper();
   void generateHUD();
  void renderMenu();
  void renderGame();
  void renderSelect();
  void update(float dt);
  void mouseMoved(sf::Event event);
  void initGameOver();



   GameObject* gameObject;

  Player player;
  Enemy enemy_easy[24];
  GameObject shots[11];

  int rows = 3;
  int col = 6;

  int score = 0;
  sf::Text score_text;
  sf::Font score_font;

  // Menu options
  sf::Text play_menu;
  sf::Text exit_menu;

  sf::Text select_title;
  sf::Text gravity_menu;
  sf::Text quadratic_menu;
  sf::Text sine_menu;
  sf::Text return_text;
  sf::Text key_exit;

  // Game Over
  sf::Text game_over_text;


  int grid_size = 10;
  int row_size = 4;

  Enemy menu_aliens[40];

  private:

   sf::RenderWindow& window;

  sf::Sprite backround;
  sf::Texture background_image;


   sf::Texture player_texture;
   sf::Texture enemy_e_texture;
   sf::Texture player_m_texture;
   sf::Texture player_h_texture;
   sf::Texture shots_texture;

   // Game Title
   sf::Text game_title;
};

#endif // SPACEINVADERSSFML_HELPER_H
