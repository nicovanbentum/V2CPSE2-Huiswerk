#ifndef _BALL_HPP
#define _BALL_HPP

#include <SFML/Graphics.hpp>

class drawable {
public:
  virtual void draw(sf::RenderWindow &window) const = 0;
};

class square : drawable {
public:
  sf::Vector2f pos;
  sf::Vector2f size;
  sf::RectangleShape body;
  sf::Vector2f lastMove;
  bool lockMovement = false;

  square(sf::Vector2f pos, sf::Vector2f size);

  void move(sf::Vector2f delta);
  void undoLastMove();

  void jump(sf::Vector2f target);
  void jump(sf::Vector2i target);

  void draw(sf::RenderWindow &window) const;
};

class walls : drawable {
public:
  walls(sf::Vector2f pos, sf::Vector2f size, int thickness = 2);

  void draw(sf::RenderWindow &window) const;

  // variables
  sf::Vector2f pos;
  sf::Vector2f size;
  int thickness;

  sf::RectangleShape left;
  sf::RectangleShape right;
  sf::RectangleShape top;
  sf::RectangleShape bottom;
};

class ball : drawable {
public:
  ball(sf::Vector2f position, float size, sf::Vector2f speed);

  void draw(sf::RenderWindow &window) const;

  void move(sf::Vector2f speed);

  void jump(sf::Vector2f target);
  void jump(sf::Vector2i target);

  bool overlaps(walls &w);

  bool overlaps(square &s);

public:
  sf::Vector2f position;
  float size;
  sf::Vector2f speed;
  sf::CircleShape body;
};

#endif
