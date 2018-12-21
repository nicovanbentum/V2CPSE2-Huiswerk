#pragma once
#include "SFML/Graphics.hpp"
#include "game_state.h"

struct gui : tic_tac_toe
{
	sf::RenderWindow window{ sf::VideoMode{850, 850}, "SFML window" };
	sf::RectangleShape blocks[3][3];

	sf::Texture eks;
	sf::Texture O;

	sf::Text turn_text;
	sf::Font turn_font;

	gui(sf::Vector2f grid_pos, sf::Vector2f block_size, float spacing);

	void run();
	void updateTextures();
	void draw();
	void handle_event(sf::Event event);
};
