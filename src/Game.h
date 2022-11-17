
#ifndef SPACEINVADERS_GAME_H
#define SPACEINVADERS_GAME_H

#include <SFML/Graphics.hpp>
#include "Vector2.h"
#include "Helper.h"
#include "GameObject.h"

class Game
{
 public:
  Game(sf::RenderWindow& window);
  ~Game();
  bool init();
  void update(float dt);
  void render(sf::Event event);
  int randomize(int min, int max);
  void keyPressed(sf::Event event);
  void movePlayer(float dt);
  void gravityCurve();
  void quadraticMode();
  void sineMode();
  void shoot();
  void shootCollision();
  void mouseClicked(sf::Event event);
  bool wallsCollision(sf::Sprite* object);
  bool isInside(sf::Event event);
  void mouseMoved(sf::Event event);
  bool insideText(sf::Event event, sf::Text* text_1);
  void resetGame();
  bool allOf();
  bool hitBottom();


  Helper* helper;
  Vector2* vector2;
  GameObject* gameObject;
  Enemy* enemy;

  enum MainState {
    main_menu,
    mode_selection,
    in_game,
    game_over
  };

  int current_main_state = main_menu;

  enum GameMode {
    space_invaders,
    gravity_curve,
    quadratic_curve,
    sine_curve,
    extra,
  };

  int current_game_mode;


 private:
  sf::RenderWindow& window;
  float shot_speed = 2.0;

  float y_value;

  float randX;
  float randY;

  int shoot_counter = 0;
  sf::Event event_mouse;

  float multiplier = 1.0;

  bool inside_play = false;
  bool inside_exit = false;

  float y_double;
  float direc;
  float moveDown;

  bool gravity_on = false;
  bool quadratic_on = false;
  bool sine_on = false;
  bool menu_on = false;

  bool transition_on = false;

  int invisible_enemies;
};

#endif // SPACEINVADERS_GAME_H
