#include "Game.h"
#include <iostream>
#include <valarray>

Game::Game(sf::RenderWindow& game_window)
  : window(game_window)
{
  srand(time(NULL));

  helper = new Helper(window);
  vector2 = new Vector2(1, 1);


}

Game::~Game()
{
  delete helper;
}

int Game::randomize(int min, int max)
{
  int value = min + rand() / (RAND_MAX /(max - min));
  return value;
}

bool Game::init()
{
  randX = randomize(-10, 10);
  randY = randomize(-10, 10);
  helper->generateHUD();
  if (current_game_mode == quadratic_curve)
  {
    for (int i = 0; i < helper->col*helper->rows; ++i)
    {
    }
  }
  return true;
}

void Game::update(float dt)
{
  movePlayer(dt);
  if (current_main_state == main_menu)
  {
    helper->score = 0;
    helper->score_text.setPosition(15, 10);
    helper->score_text.setCharacterSize(40);
    helper->score_text.setString(std::to_string((helper->score)));
  }
  if (current_main_state == in_game)
  {
    shootCollision();
    for (auto& shot : helper->shots)
    {
      if (shot.visibility)
      {
        shot.getSprite()->move(0, -100 * shot_speed * dt);
      }
    }
    if (current_game_mode == gravity_curve)
    {
      gravityCurve();
    }
    else if (current_game_mode == quadratic_curve)
    {
      quadraticMode();
    }
    else if (current_game_mode == sine_curve)
    {
      sineMode();
    }
    if (allOf() || hitBottom())
    {
      current_main_state = game_over;
    }
  }
  if (current_main_state == game_over)
  {
    resetGame();
  }
}

void Game::render(sf::Event event)
{
  if (current_main_state == main_menu)
  {
    helper->renderMenu();
    if (insideText(event, &helper->play_menu))
    {
      inside_play = true;
      helper->play_menu.setCharacterSize(60);
      helper->play_menu.setFillColor(sf::Color::Red);
      helper->play_menu.setPosition(window.getSize().x /2 - helper->play_menu.getLocalBounds().width/2 - 8, window.getSize().y /2 - helper->play_menu.getGlobalBounds().height / 2);
    }
    else{
      inside_play = false;
      helper->play_menu.setCharacterSize(40);
      helper->play_menu.setFillColor(sf::Color::White);
      helper->play_menu.setPosition(window.getSize().x /2 - helper->play_menu.getLocalBounds().width/2 - 8, window.getSize().y /2 - helper->play_menu.getGlobalBounds().height / 3);
    }
    if (insideText(event, &helper->exit_menu))
    {
      inside_exit = true;
      helper->exit_menu.setCharacterSize(60);
      helper->exit_menu.setFillColor(sf::Color::Red);
      helper->exit_menu.setPosition(window.getSize().x /2 - helper->exit_menu.getLocalBounds().width/2 - 8, window.getSize().y /2 - helper->exit_menu.getGlobalBounds().height / 3 + 120);
    }
    else{
      inside_exit = false;
      helper->exit_menu.setCharacterSize(40);
      helper->exit_menu.setFillColor(sf::Color::White);
      helper->exit_menu.setPosition(window.getSize().x /2 - helper->exit_menu.getLocalBounds().width/2 - 8, window.getSize().y /2 - helper->exit_menu.getGlobalBounds().height / 3 + 120);
    }
  }

  else if (current_main_state == mode_selection)
  {
    helper->renderSelect();
    if (insideText(event, &helper->gravity_menu))
    {
      gravity_on = true;
      helper->gravity_menu.setCharacterSize(50);
      helper->gravity_menu.setFillColor(sf::Color::Red);
      helper->gravity_menu.setPosition(window.getSize().x/3 - 65, window.getSize().y /2 - helper->gravity_menu.getGlobalBounds().height / 3 - 120);
    }
    else
    {
      gravity_on = false;
      helper->gravity_menu.setCharacterSize(40);
      helper->gravity_menu.setFillColor(sf::Color::White);
      helper->gravity_menu.setPosition(window.getSize().x/3 - 29, window.getSize().y /2 - helper->gravity_menu.getGlobalBounds().height / 3 - 120);
    }
    if (insideText(event, &helper->quadratic_menu))
    {
      quadratic_on = true;
      helper->quadratic_menu.setCharacterSize(50);
      helper->quadratic_menu.setFillColor(sf::Color::Red);
      helper->quadratic_menu.setPosition(window.getSize().x /3 - 96, window.getSize().y /2 - helper->quadratic_menu.getGlobalBounds().height / 3);
    }
    else{
      quadratic_on = false;
      helper->quadratic_menu.setCharacterSize(40);
      helper->quadratic_menu.setFillColor(sf::Color::White);
      helper->quadratic_menu.setPosition(window.getSize().x /3 - 60, window.getSize().y /2 - helper->quadratic_menu.getGlobalBounds().height / 3);
    }
    if (insideText(event, &helper->sine_menu))
    {
      sine_on = true;
      helper->sine_menu.setCharacterSize(50);
      helper->sine_menu.setFillColor(sf::Color::Red);
      helper->sine_menu.setPosition(window.getSize().x /3 - 34, window.getSize().y /2 - helper->sine_menu.getGlobalBounds().height / 3 + 120);
    }
    else
    {
      sine_on = false;
      helper->sine_menu.setCharacterSize(40);
      helper->sine_menu.setFillColor(sf::Color::White);
      helper->sine_menu.setPosition(window.getSize().x /3 - 2, window.getSize().y /2 - helper->sine_menu.getGlobalBounds().height / 3 + 120);
    }
    if (insideText(event, &helper->return_text))
    {
      menu_on = true;
      helper->return_text.setCharacterSize(50);
      helper->return_text.setFillColor(sf::Color::Red);
      helper->return_text.setPosition(window.getSize().x /3 + 10, window.getSize().y /2 - helper->return_text.getGlobalBounds().height / 3 + 240);
    }
    else
    {
      menu_on = false;
      helper->return_text.setCharacterSize(40);
      helper->return_text.setFillColor(sf::Color::White);
      helper->return_text.setPosition(window.getSize().x /3 + 23, window.getSize().y /2 - helper->return_text.getGlobalBounds().height / 3 + 240);
    }
  }
  else if (current_main_state == in_game)
  {
    helper->renderGame();
  }
  else if (current_main_state == game_over)
  {
    helper->initGameOver();
    if (insideText(event, &helper->return_text))
    {
      menu_on = true;
      helper->return_text.setCharacterSize(50);
      helper->return_text.setFillColor(sf::Color::Red);
      helper->return_text.setPosition(window.getSize().x /3 + 10, window.getSize().y /2 - helper->return_text.getGlobalBounds().height / 3 + 240);
    }
    else
    {
      menu_on = false;
      helper->return_text.setCharacterSize(40);
      helper->return_text.setFillColor(sf::Color::White);
      helper->return_text.setPosition(window.getSize().x /3 + 23, window.getSize().y /2 - helper->return_text.getGlobalBounds().height / 3 + 240);
    }
  }
}

void Game::keyPressed(sf::Event event)
{
  if (current_main_state == in_game)
  {
    if (event.key.code == sf::Keyboard::Space)
    {
      shoot();
    }
  }
  if (event.key.code == sf::Keyboard::Q)
  {
    current_main_state = main_menu;
    current_game_mode = space_invaders;
    resetGame();
  }
}


void Game::mouseMoved(sf::Event event)
{
  helper->mouseMoved(event);
}

void Game::movePlayer(float dt)
{
  auto keyA = sf::Keyboard::isKeyPressed(sf::Keyboard::A);
  auto keyD = sf::Keyboard::isKeyPressed(sf::Keyboard::D);
  auto keyW = sf::Keyboard::isKeyPressed(sf::Keyboard::W);
  auto keyS = sf::Keyboard::isKeyPressed(sf::Keyboard::S);

  if (current_game_mode == gravity_curve || current_game_mode == quadratic_curve || current_game_mode == sine_curve)
  {
    if (keyA)
    {
      helper->player.moveRight();
    }
    else if (keyD)
    {
      helper->player.moveLeft();
    }
  }
  else
  {
    if (keyW)
    {
      if (helper->player.getSprite()->getPosition().y >= window.getSize().y / 1.5)
      {
        helper->player.moveUp();
      }
    }
    else if (keyS)
    {
      helper->player.moveDown();
    }
  }
    if (
      (helper->player.getSprite()->getPosition().x +
       helper->player.getSprite()->getGlobalBounds().width) >=
      window.getSize().x - 2)
    {
      helper->player.getSprite()->move(-8, 0);
    }
    else if (helper->player.getSprite()->getPosition().x <= 0)
    {
      helper->player.getSprite()->move(8, 0);
    }
    if (helper->player.getSprite()->getPosition().y <= 0)
    {
      helper->player.getSprite()->move(0, 8);
    }
    else if (
      helper->player.getSprite()->getPosition().y +
        helper->player.getSprite()->getGlobalBounds().height >=
      window.getSize().y)
    {
      helper->player.getSprite()->move(0, -8);
    }
}

/// Use enemies' own vector to make something interesting

void Game::gravityCurve()
{

  for (int i = 0; i < helper->rows*helper->col; i++)
  {
    y_double = fabsf(helper->enemy_easy[i].getSprite()->getPosition().y  + 0.001f) * 0.006f;
    helper->enemy_easy[i].getSprite()->move(helper->enemy_easy[i].vector2->x * helper->enemy_easy[i].getEnemySpeed() * 0.4f, y_double);
    helper->enemy_easy[i].vector2->normalise();

    if (wallsCollision(helper->enemy_easy[i].getSprite()))
    {
      helper->enemy_easy[i].vector2->x = -helper->enemy_easy[i].vector2->x;
    }
    if (helper->enemy_easy[i].visibility)
    {
      if (gameObject->collisionCheck(
            helper->player.getSprite(), helper->enemy_easy[i].getSprite()))
      {
        current_main_state = game_over;
        resetGame();
      }
    }
  }

  // Not the right curve
//  for (int i = 0; i < helper->rows*helper->col; i++)
//  {
//    y_double = (helper->enemy_easy[i].getSprite()->getPosition().x*helper->enemy_easy[i].getSprite()->getPosition().x) * helper->enemy_easy[i].getEnemySpeed();
//    helper->enemy_easy[i].getSprite()->move(helper->enemy_easy[i].vector2->x * helper->enemy_easy->getEnemySpeed() * 0.4f, y_double * 0.0000008f);
//    helper->enemy_easy[i].vector2->normalise();
//
//    if (helper->enemy_easy[i].getSprite()->getPosition().x + helper->enemy_easy[i].getSprite()->getGlobalBounds().width >= window.getSize().x)
//    {
//      helper->enemy_easy[i].vector2->x = -helper->enemy_easy[i].vector2->x;
//    }
//    else if (helper->enemy_easy[i].getSprite()->getPosition().x <= 0)
//    {
//      helper->enemy_easy[i].vector2->x = -helper->enemy_easy[i].vector2->x;
//    }
//    if (gameObject->collisionCheck(
//              helper->player.getSprite(), helper->enemy_easy[i].getSprite()))
//        {
//          std::cout << "COLLISIONNNN!!!!" << std::endl;
//        }
//  }

  // Cool movement
//  for (int i = 0; i < helper->col * helper->rows; ++i)
//  {
//    float y_value =
//      helper->enemy_easy[i - 1].getSprite()->getPosition().y * -0.003;
//    helper->enemy_easy[i].vector2->normalise();
//
//    helper->enemy_easy[i].getSprite()->move(
//      helper->enemy_easy[i].vector2->x, y_value);
//
//    if (
//      helper->enemy_easy[i].getSprite()->getPosition().x +
//        helper->enemy_easy->getSprite()->getGlobalBounds().width >
//      window.getSize().x)
//    {
//      helper->enemy_easy[i].vector2->x = -helper->enemy_easy[i].vector2->x;
//    }
//    else if (helper->enemy_easy[i].getSprite()->getPosition().x <= 0)
//    {
//      helper->enemy_easy[i].vector2->x = -helper->enemy_easy[i].vector2->x;
//    }
//  }

  //  for (int i = 0; i < helper->col * helper->rows; ++i)
//  {
//    if (helper->enemy_easy[i].visibility)
//    {
//      helper->enemy_easy[i].getSprite()->move(helper->enemy_easy[i].getEnemySpeed() * vector2->x, y_value * vector2->y * (multiplier / i) * multiplier);
//      if (helper->enemy_easy[i].getSprite()->getPosition().x + helper->enemy_easy->getSprite()->getGlobalBounds().width > window.getSize().x)
//      {
//        vector2->x = -vector2->x;
//      }
//      else if (helper->enemy_easy[i].getSprite()->getPosition().x <= 0)
//      {
//        vector2->x = -vector2->x;
//      }
//
//      if (gameObject->collisionCheck(
//        helper->player.getSprite(), helper->enemy_easy[i].getSprite()))
//      {
//        std::cout << "COLLISIONNNN!!!!" << std::endl;
//      }
//    }
//    y_value += 0.3;
//  }


  // Without bug

//  for (int i = 0; i < helper->col * helper->rows; ++i)
//  {
//    if (helper->enemy_easy->visibility)
//    {
//      if (vector2->x > 0)
//      {
//        if (
//          helper->enemy_easy[i].getSprite()->getPosition().x +
//            helper->enemy_easy[i].getSprite()->getGlobalBounds().width >
//          window.getSize().x)
//        {
//          vector2->x = -vector2->x;
//        }
//      }
//      else if (vector2->x < 0)
//      {
//        if (helper->enemy_easy[i].getSprite()->getPosition().x <= 0)
//        {
//          vector2->x = -vector2->x;
//        }
//      }
//      if (gameObject->collisionCheck(
//            helper->player.getSprite(), helper->enemy_easy[i].getSprite()))
//      {
//        std::cout << "COLLISIONNNN!!!!" << std::endl;
//      }
//    }
//    helper->enemy_easy[i].getSprite()->move(
//      (enemy_speed * vector2->x) / 2, vector2->y / 2);
//  }
}


void Game::quadraticMode()
{
  for (int i = 0; i < helper->rows*helper->col; ++i)
  {
    y_double = (int(helper->enemy_easy[i].getSprite()->getPosition().x)^2) * (window.getSize().x/2);
    moveDown = (0.0045f * (helper->enemy_easy[i].getSprite()->getPosition().x * helper->enemy_easy[i].getSprite()->getPosition().x) / window.getSize().x/2 - 0.2f);
    direc = (1.0f * helper->enemy_easy[i].getEnemySpeed() * 0.6f);

    if ((helper->enemy_easy[i].getSprite()->getPosition().x + helper->enemy_easy[i].getSprite()->getGlobalBounds().width) >= window.getSize().x)
    {
      helper->enemy_easy[i].vector2->x = -helper->enemy_easy[i].vector2->x;
      moveDown = -moveDown;
      helper->enemy_easy[i].vector2->normalise();
    }
    else if (helper->enemy_easy[i].getSprite()->getPosition().x <= 0)
    {
      helper->enemy_easy[i].vector2->x = -helper->enemy_easy[i].vector2->x;
      helper->enemy_easy[i].vector2->normalise();
    }

    helper->enemy_easy[i].getSprite()->move(direc * helper->enemy_easy[i].vector2->x * 3.2f, moveDown);
    helper->enemy_easy[i].vector2->normalise();
    if (helper->enemy_easy[i].visibility)
    {
      if (gameObject->collisionCheck(
            helper->player.getSprite(), helper->enemy_easy[i].getSprite()))
      {
        current_main_state = game_over;
        resetGame();
      }
    }
  }

  //  for (int i = 0; i < helper->col * helper->rows; ++i)
//  {
//    helper->enemy_easy->vector2->y = (helper->enemy_easy[0].getSprite()->getPosition().x*helper->enemy_easy[0].getSprite()->getPosition().x);
//    //helper->enemy_easy[0].vector2->normalise();
//    std::cout << "vdctor= " << helper->enemy_easy[0].vector2->y << std::endl;
//    helper->enemy_easy[0].getSprite()->move(helper->enemy_easy[0].vector2->x * helper->enemy_easy[0].getEnemySpeed() * 0.0009, helper->enemy_easy[0].vector2->y * 0.00002);
////    helper->enemy_easy[0].vector2->normalise();
//
//    if ((helper->enemy_easy[0].getSprite()->getPosition().x + helper->enemy_easy[0].getSprite()->getGlobalBounds().width) / 2 >= window.getSize().x / 2)
//    {
//      helper->enemy_easy[0].vector2->normalise();
//      helper->enemy_easy[0].vector2->y *= -helper->enemy_easy[0].vector2->y;;
//      std::cout << "mid" << std::endl;
//
//    }
//  }

  //  for (int i = 0; i < helper->col * helper->rows; ++i)
//  {
//    y_value = (int(helper->enemy_easy[i].getSprite()->getPosition().y)^2) * 0.0005;
//    helper->enemy_easy[i].getSprite()->move(helper->enemy_easy[i].vector2->x * helper->enemy_easy[i].getEnemySpeed() * 0.05, y_value * 0.3);
//    helper->enemy_easy[i].vector2->normalise();
//    if (helper->enemy_easy[i].getSprite()->getPosition().x + helper->enemy_easy[i].getSprite()->getGlobalBounds().width / 2 >= window.getSize().x / 2)
//    {
//      y_value = -y_value;
//    }
////    else
////    {
////      helper->enemy_easy[0].vector2->y =
////        int(helper->enemy_easy[0].vector2->y) ^ 2;
////    }
//
//
//    std::cout << "vdctor= " << y_value << std::endl;
//
//
//  }


  //  float quadratic = helper->enemy_easy[0].getSprite()->getPosition().x ;
//  int test = (int(helper->enemy_easy[0].getSprite()->getPosition().x) ^ 2) * 0.02;
//  float move_x = helper->enemy_easy[0].getEnemySpeed() * vector2->x;
//
//
//  if (test >= window.getSize().x ||
//      test <= 0)
//  {
//    test= -test;
//  }
//  std::cout << "First= " << (helper->enemy_easy[0].getSprite()->getPosition().x*helper->enemy_easy[0].getSprite()->getPosition().x) << std::endl;
//  std::cout << "Second= " << test << std::endl;
//  helper->enemy_easy[0].getSprite()->move(move_x, test * vector2->y);
}

void Game::sineMode()
{
  for (int i = 0; i < helper->col*helper->rows; ++i)
  {
    helper->enemy_easy[i].vector2->x = 0.1f;
    helper->enemy_easy[i].getSprite()->move((helper->enemy_easy[i].vector2->x * helper->enemy_easy[i].getEnemySpeed()) * 1.5f, sin(helper->enemy_easy[i].getSprite()->getPosition().x) * 2.02f);
    if (wallsCollision(helper->enemy_easy[i].getSprite()))
    {
      helper->enemy_easy[i].vector2->x = -helper->enemy_easy[i].vector2->x;
      helper->enemy_easy[i].getSprite()->setPosition(helper->enemy_easy[i].getSprite()->getPosition().x, helper->enemy_easy[i].getSprite()->getPosition().y + helper->enemy_easy[i].getSprite()->getGlobalBounds().width);
    }
    if (helper->enemy_easy[i].visibility)
    {
      if (gameObject->collisionCheck(
            helper->player.getSprite(), helper->enemy_easy[i].getSprite()))
      {
        current_main_state = game_over;
        resetGame();
      }
    }
  }
}

void Game::shoot()
{
  if (shoot_counter <= 10)
  {
    helper->shots[shoot_counter].visibility = true;
    helper->shots[shoot_counter].getSprite()->setPosition(
      helper->player.getSprite()->getPosition().x +
        helper->player.getSprite()->getGlobalBounds().width / 2,
      helper->player.getSprite()->getPosition().y - 2);
    shoot_counter += 1;
  }
  else if (shoot_counter >= 10)
  {
    for (auto & shot : helper->shots)
    {
      if (shot.getSprite()->getPosition().y < window.getSize().y / 3 || !shot.visibility)
      {
        shoot_counter = 0;
      }
    }
  }
}


void Game::shootCollision()
{
  for (int i = 0; i < helper->col * helper->rows; ++i)
  {
    for (auto& shot : helper->shots)
    {
      if ((helper->enemy_easy[i].visibility) && (shot.visibility))
      {
        if (gameObject->collisionCheck(
              shot.getSprite(), helper->enemy_easy[i].getSprite()))
        {
          shot.visibility                  = false;
          helper->enemy_easy[i].visibility = false;
          invisible_enemies += 1;
          helper->score += 10 * multiplier;
          helper->score_text.setString(std::to_string((helper->score)));
        }
        if (
          shot.getSprite()->getPosition().y +
            shot.getSprite()->getGlobalBounds().height <
          0)
        {
          shot.visibility = false;
        }
      }
    }
  }
}
bool Game::wallsCollision(sf::Sprite* object)
{
  if (object->getPosition().x <= 0 ||
      object->getPosition().x + object->getGlobalBounds().width >= window.getSize().x ||
      object->getPosition().y <= 0 ||
      object->getPosition().y + object->getGlobalBounds().height >= window.getSize().y)
  {
   return true;
  }
  return false;
}

void Game::mouseClicked(sf::Event event)
{
  //get the click position
  sf::Vector2i click = sf::Mouse::getPosition(window);
  if (event.type == sf::Event::MouseButtonPressed)
  {
    if (current_main_state == main_menu)
    {
      if (event.mouseButton.button == sf::Mouse::Left)
      {
        if (inside_play)
        {
          current_main_state = mode_selection;
        }
        else if (inside_exit)
        {
          window.close();
        }
      }
    }
    else if (current_main_state == mode_selection)
    {
      if (gravity_on)
      {
        current_game_mode = gravity_curve;
        current_main_state = in_game;
      }
      else if (quadratic_on)
      {
        current_game_mode = quadratic_curve;
        current_main_state = in_game;
      }
      else if (sine_on)
      {
        current_game_mode = sine_curve;
        current_main_state = in_game;
      }
      else if (menu_on)
      {
        current_main_state = main_menu;
      }
    }
    else if (current_main_state == game_over)
    {
      if (menu_on)
      {
        current_main_state = main_menu;
      }
    }
  }
  
}
bool Game::insideText(sf::Event event, sf::Text* text_1)
{
  if (
    event.mouseMove.x > text_1->getPosition().x &&
    text_1->getGlobalBounds().width + text_1->getPosition().x + 12 > event.mouseMove.x &&
    event.mouseMove.y > text_1->getPosition().y &&
    text_1->getPosition().y + text_1->getGlobalBounds().height + 12 > event.mouseMove.y
    )
  {
    return true;
  }
  return false;
}
void Game::resetGame()
{
  helper->score_text.setCharacterSize(40);
  helper->score_text.setPosition(15, 10);
  helper->score_text.setString(std::to_string((helper->score)));
  for (auto & shot : helper->shots)
  {
    shot.visibility = false;
  }
  for (int i = 0; i < helper->col*helper->rows; ++i)
  {
    helper->enemy_easy[i].visibility = true;
    helper->enemy_easy[i].vector2->x = 0.707107;
//    if (helper->enemy_easy[i].vector2->x > 0.1f)
//    {
//      helper->enemy_easy[i].vector2->x = 0.1f;
//    }
//    helper->enemy_easy[i].vector2->normalise();
//    std::cout << helper->enemy_easy[i].vector2->x << std::endl;
//    if (helper->enemy_easy[i].vector2->x < 0)
//    {
//      helper->enemy_easy[i].vector2->x = -helper->enemy_easy[i].vector2->x;
//      std::cout << helper->enemy_easy[i].vector2->x << std::endl;
//    }
  }
  for (int i = 0; i < helper->rows; ++i)
  {
    for (int j = 0; j < helper->col; ++j)
    {
      helper->enemy_easy[i * helper->col + j].getSprite()->setPosition(j * 70 + 25, 15 + i * (helper->enemy_easy->getSprite()->getPosition().y + helper->enemy_easy->getSprite()->getGlobalBounds().height) + 20);
    }
  }
}

bool Game::allOf()
{
  int j = 0;
  for (int i = 0; i < helper->col*helper->rows; ++i)
  {
    if (helper->enemy_easy[i].visibility)
    {
      j += 1;
    }
  }
  if (j == 0)
  {
    return true;
  }
  else
  {
    return false;
  }
}

bool Game::hitBottom()
{
  int j = 0;
  for (int i = 0; i < helper->col*helper->rows; ++i)
  {
    if (helper->enemy_easy[i].getSprite()->getPosition().y <= window.getSize().y)
    {
      j += 1;
    }
  }
  if (j == 0)
  {
    return true;
  }
  else
  {
    return false;
  }
}