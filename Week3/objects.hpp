#ifndef _BALL_HPP
#define _BALL_HPP

#include <SFML/Graphics.hpp>
#include <functional>

struct drawable 
{
	virtual void draw(sf::RenderWindow &window) const		= 0;
	virtual void setSize(sf::Vector2f size)					= 0;
	virtual sf::Vector2f getSize()							= 0;
	virtual sf::Shape& Body()								= 0;

	virtual ~drawable() {}

	std::string id;
	bool isSelected = false;
};

struct rectangle : drawable 
{
  //constructors
  rectangle(sf::Vector2f pos, sf::Vector2f size);
  rectangle();

  //member functions
  void draw(sf::RenderWindow &window) const;
  void setSize(sf::Vector2f size);
  sf::Vector2f getSize();
  sf::Shape& Body();
  
  // variables
  sf::RectangleShape body;
};

struct ball : drawable 
{
  //constructors
  ball(sf::Vector2f position, float size);
  ball();

  //member functions
  void draw(sf::RenderWindow &window) const;
  void setSize(sf::Vector2f size);
  sf::Vector2f getSize();
  sf::Shape& Body();

  //variables
  sf::CircleShape body;
};

struct line : drawable
{
	//constructors
	line(sf::Vector2f start, float length, float thickness);

	//member functions
	void draw(sf::RenderWindow &window) const;
	void setSize(sf::Vector2f size);
	sf::Vector2f getSize();
	sf::Shape& Body();

	//variables
	sf::RectangleShape body;
};

#endif
