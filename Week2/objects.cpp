#include "objects.hpp"
#include <SFML/Graphics.hpp>

square::square(sf::Vector2f pos, sf::Vector2f size) : pos(pos), size(size) {
  body.setPosition(pos);
  body.setSize(size);
  body.setFillColor(sf::Color::Yellow);
}

void square::move(sf::Vector2f delta) {
  body.setPosition(body.getPosition() + delta);
}

void square::jump(sf::Vector2f target) { body.setPosition(target); }

void square::jump(sf::Vector2i target) {
  jump(
      sf::Vector2f(static_cast<float>(target.x), static_cast<float>(target.y)));
}

void square::draw(sf::RenderWindow &window) const { window.draw(body); }

walls::walls(sf::Vector2f pos, sf::Vector2f size, int thickness)
    : pos(pos), size(size), thickness(thickness) {
  top.setPosition(pos);
  top.setSize(sf::Vector2f(size.x, thickness));

  left.setPosition(sf::Vector2f(pos.x, pos.y + thickness));
  left.setSize(sf::Vector2f(thickness, size.y));

  right.setPosition(sf::Vector2f((pos.x + size.x) - thickness, pos.y));
  right.setSize(sf::Vector2f(thickness, size.y));

  bottom.setPosition(sf::Vector2f(pos.x, pos.y + size.y));
  bottom.setSize(sf::Vector2f(size.x, thickness));
}

void walls::draw(sf::RenderWindow &window) const {
  window.draw(left);
  window.draw(right);
  window.draw(top);
  window.draw(bottom);
}

ball::ball(sf::Vector2f position, float size, sf::Vector2f speed)
    : position{position}, size{size}, speed{speed} {
  body.setFillColor(sf::Color::Blue);
  body.setPosition(position);
  body.setRadius(size);
}

void ball::draw(sf::RenderWindow &window) const { window.draw(body); }

void ball::move(sf::Vector2f delta) {
  body.setPosition(body.getPosition() + delta);
}

void ball::jump(sf::Vector2f target) { position = target; }

void ball::jump(sf::Vector2i target) {
  jump(
      sf::Vector2f(static_cast<float>(target.x), static_cast<float>(target.y)));
}

bool ball::overlaps(walls &w) {

  if (body.getGlobalBounds().intersects(w.left.getGlobalBounds()) ||
      body.getGlobalBounds().intersects(w.right.getGlobalBounds()) ||
      body.getGlobalBounds().intersects(w.top.getGlobalBounds()) ||
      body.getGlobalBounds().intersects(w.bottom.getGlobalBounds())) {
    return true;
  }
  return false;
}

bool ball::overlaps(square &s) {
  if (body.getGlobalBounds().intersects(s.body.getGlobalBounds())) {
    return true;
  }
  return false;
}
