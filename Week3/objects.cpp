#include "objects.hpp"
#include <SFML/Graphics.hpp>

rectangle::rectangle(sf::Vector2f pos, sf::Vector2f size)
{
	id = "RECTANGLE";
	body.setPosition(pos);
	body.setSize(size);

}

rectangle::rectangle()
{}

void rectangle::draw(sf::RenderWindow &window) const {
	window.draw(body);
}

ball::ball(sf::Vector2f position, float size)
{
	id = "BALL";
	body.setFillColor(sf::Color::Blue);
	body.setPosition(position);
	body.setRadius(size);
}

ball::ball()
{}

void ball::draw(sf::RenderWindow &window) const { window.draw(body); }

line::line(sf::Vector2f start, float length, float thickness)
{
	id = "LINE";
	body.setPosition(start);
	body.setSize(sf::Vector2f(length, thickness));
}

void line::draw(sf::RenderWindow & window) const { window.draw(body); }

sf::Vector2f rectangle::getSize()
{
	return body.getSize();
}

void rectangle::setSize(sf::Vector2f size)
{
	body.setSize(size);
}

sf::Vector2f ball::getSize()
{
	return sf::Vector2f(body.getRadius(), body.getRadius());
}

void ball::setSize(sf::Vector2f size)
{
	body.setRadius(size.x);
}

sf::Vector2f line::getSize()
{
	return body.getSize();
}

void line::setSize(sf::Vector2f size)
{
	body.setSize(size);
}

sf::Shape& rectangle::Body()
{
	return body;
}

sf::Shape& line::Body()
{
	return body;
}

sf::Shape& ball::Body()
{
	return body;
}