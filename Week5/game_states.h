#ifndef GAME_STATES_H
#define GAME_STATES_H

#include "SFML/Graphics.hpp"
#include "commands.h"
#include <vector>
#include <iostream>
#include <algorithm>

struct tic_tac_toe
{
	char grid[3][3] = {};
	char turn = 'X';

	std::vector<command *> list_of_commands;

	virtual ~tic_tac_toe() {}
	virtual void draw() = 0;
	void replay();
	char check_win_condition();
	bool check_game_over();

};

struct command_line : tic_tac_toe
{
	command_line() {}

	int x;
	int y;

	void run();
	void draw() override;
};

struct gui : tic_tac_toe
{
	sf::RenderWindow & window;
	sf::RectangleShape blocks[3][3];

	sf::Texture eks;
	sf::Texture O;

	sf::Text turn_text;
	sf::Font turn_font;

	gui(sf::RenderWindow & window, sf::Vector2f grid_pos, sf::Vector2f block_size, float spacing);

	void updateTextures();
	void draw();
	void handle_event(sf::Event event);
};

#endif
