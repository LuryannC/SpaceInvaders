//
// Created by l2-augustocerv on 21/02/2022.
//

#include "Helper.h"
#include "iostream"

Helper::Helper(sf::RenderWindow& game_window) : window(game_window)
{

}

Helper::~Helper()
{

}

void Helper::generateHUD()
{
  background_image.loadFromFile("Data/Images/bg.jpg");
  backround.setTexture(background_image);

  for (int i = 0; i < grid_size*row_size; ++i)
  {
    menu_aliens[i].initialiseSprite(enemy_e_texture, "Data/Images/SpaceShooterRedux/PNG/Enemies/enemyBlack5.png");
    menu_aliens[i].getSprite()->setScale(0.4f, 0.4f);
    
  }

  
  // Score
  score_text.setString(std::to_string((score)));
  score_text.setFont(score_font);
  score_text.setCharacterSize(40);
  score_text.setPosition(15, 10);



  // Game title
  game_title.setString("   Space \nInvaders");
  game_title.setFont(score_font);
  game_title.setFillColor(sf::Color::White);
  game_title.setPosition(window.getSize().x /2 - 130,  62);
  game_title.setCharacterSize(60);

  // Game Over
  game_over_text.setString("Game Over");
  game_over_text.setFont(score_font);
  game_over_text.setFillColor(sf::Color::White);
  game_over_text.setPosition(window.getSize().x /3 - 150,  20);
  game_over_text.setCharacterSize(120);

  // Score
  score_text.setString(std::to_string((score)));
  score_text.setFont(score_font);
  score_text.setCharacterSize(40);
  score_text.setPosition(15, 10);

  // Menu options
  play_menu.setString("Play");
  play_menu.setFont(score_font);
  play_menu.setFillColor(sf::Color::White);
  //play_menu.setPosition(window.getSize().x /2 - play_menu.getLocalBounds().width/2 - 20, window.getSize().y /2 - play_menu.getGlobalBounds().height / 3);
  play_menu.setPosition(window.getSize().x /2 - play_menu.getLocalBounds().width/2 - 17, window.getSize().y /2 - play_menu.getGlobalBounds().height / 3);
  play_menu.setCharacterSize(40);

  // Menu options
  exit_menu.setString("Exit");
  exit_menu.setFont(score_font);
  exit_menu.setFillColor(sf::Color::White);
  exit_menu.setPosition(window.getSize().x /2 - exit_menu.getLocalBounds().width/2 - 14, window.getSize().y /2 - exit_menu.getGlobalBounds().height / 3 + 120);
  exit_menu.setCharacterSize(40);

  // Game title
  select_title.setString("      Select \nGame Mode");
  select_title.setFont(score_font);
  select_title.setFillColor(sf::Color::White);
  select_title.setPosition(window.getSize().x /2 - 180,  62);
  select_title.setCharacterSize(60);

  // Menu options
  gravity_menu.setString("Gravity Curve");
  gravity_menu.setFont(score_font);
  gravity_menu.setFillColor(sf::Color::White);
  //gravity_menu.setPosition(window.getSize().x /2 - gravity_menu.getLocalBounds().width/2 - 20, window.getSize().y /2 - gravity_menu.getGlobalBounds().height / 3);
  gravity_menu.setPosition(window.getSize().x/3 - 29, window.getSize().y /2 - gravity_menu.getGlobalBounds().height / 3 - 120);
  gravity_menu.setCharacterSize(40);

  // Menu options
  quadratic_menu.setString("Quadratic Curve");
  quadratic_menu.setFont(score_font);
  quadratic_menu.setFillColor(sf::Color::White);
  quadratic_menu.setPosition(window.getSize().x /3 - 60, window.getSize().y /2 - quadratic_menu.getGlobalBounds().height / 3);
  quadratic_menu.setCharacterSize(40);

  // Menu options
  sine_menu.setString("Sine Curve");
  sine_menu.setFont(score_font);
  sine_menu.setFillColor(sf::Color::White);
  sine_menu.setPosition(window.getSize().x /3 - 2, window.getSize().y /2 - sine_menu.getGlobalBounds().height / 3 + 120);
  sine_menu.setCharacterSize(40);

  // Menu options
  return_text.setString("Return");
  return_text.setFont(score_font);
  return_text.setFillColor(sf::Color::White);
  return_text.setPosition(window.getSize().x /3 + 23, window.getSize().y /2 - return_text.getGlobalBounds().height / 3 + 240);
  return_text.setCharacterSize(40);

  game_over_text.setString("Game Over");
  game_over_text.setFont(score_font);
  game_over_text.setFillColor(sf::Color::White);
  game_over_text.setPosition(window.getSize().x /2 - 230,  62);
  game_over_text.setCharacterSize(80);

  // exit key
  key_exit.setString("Q to exit");
  key_exit.setFont(score_font);
  key_exit.setCharacterSize(40);
  key_exit.setPosition(window.getSize().x / 2 + 110, 10);

  // Player
  if (!score_font.loadFromFile("Data/Fonts/OpenSans-Bold.ttf")){
    std::cout << "Title font did not load" << std::endl;
  }
  player.initialiseSprite(player_texture, "Data/Images/SpaceShooterRedux/PNG/playerShip1_blue.png");
  player.getSprite()->setPosition(10, window.getSize().y - player.getSprite()->getGlobalBounds().height - 2);
  player.getSprite()->setScale(0.6, 0.6);

  // Shots

  for (auto & shot : shots)
  {
    shot.initialiseSprite(shots_texture, "Data/Images/SpaceShooterRedux/PNG/Lasers/laserBlue01.png");
    shot.visibility = false;
    shot.getSprite()->setPosition(0, 0);
    shot.getSprite()->setScale(0.5,0.5);
  }


  // Enemies

  // Easy 1 hit
  for (int i = 0; i < rows; ++i)
  {
    for (int j = 0; j < col; ++j)
    {
      enemy_easy[i * col + j].initialiseSprite(enemy_e_texture, "Data/Images/SpaceShooterRedux/PNG/Enemies/enemyBlack5.png");
      enemy_easy[i * col + j].getSprite()->setScale(0.6, 0.6);
      enemy_easy[i * col + j].getSprite()->setPosition(j * 70 + 25, 15 + i * (enemy_easy->getSprite()->getPosition().y + enemy_easy->getSprite()->getGlobalBounds().height) + 20);

    }
  }

}

void Helper::update(float dt)
{

}

void Helper::renderMenu()
{
  window.draw(backround);
  for (int i = 0; i < grid_size; ++i)
  {
    for (int j = 0; j < row_size; ++j)
    {
      window.draw(*menu_aliens[i].getSprite());
      menu_aliens[i].getSprite()->setPosition(menu_aliens[i+1].getSprite()->getPosition().x  + 50,
                                 40 * j + 220);
    }
  }

  window.draw(game_title);
  window.draw(play_menu);
  window.draw(exit_menu);
}



void Helper::renderGame()
{
  window.draw(backround);
  window.draw(*player.getSprite());
  window.draw(score_text);
  window.draw(key_exit);
  for (int i = 0; i < rows * col; ++i)
  {
    if (enemy_easy[i].visibility)
    {
      window.draw(*enemy_easy[i].getSprite());
    }
  }
  for (auto & shot : shots)
  {
    if(shot.visibility)
    {
      window.draw(*shot.getSprite());
    }
  }
}

void Helper::mouseMoved(sf::Event event)
{


}
void Helper::renderSelect()
{
  window.draw(backround);
  window.draw(select_title);
  window.draw(gravity_menu);
  window.draw(quadratic_menu);
  window.draw(sine_menu);
  window.draw(return_text);
}

void Helper::initGameOver()
{
  window.draw(backround);
  score_text.setPosition(window.getSize().x / 2 - (score_text.getGlobalBounds().width / 2) - 20, 250);
  score_text.setCharacterSize(80);
  window.draw(game_over_text);
  window.draw(score_text);
  window.draw(return_text);
}
