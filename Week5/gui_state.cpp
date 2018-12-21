#pragma once
#include "SFML/Graphics.hpp"
#include "gui_state.h"

void gui::run()
{
	while (window.isOpen()) {
		window.clear();

		draw();

		window.display();
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				window.close();
			}
			handle_event(event);
		}
	}
}

gui::gui(sf::Vector2f grid_pos, sf::Vector2f block_size, float spacing) {

	window.setKeyRepeatEnabled(false);
	window.setFramerateLimit(60);

	int i = 0;
	sf::Vector2f next_pos = grid_pos;
	for (auto & row : blocks)
	{
		for (auto & b : row)
		{
			i++;

			b.setPosition(next_pos);
			b.setSize(block_size);
			b.setFillColor(sf::Color::White);
			next_pos.x += block_size.x + spacing;

			if ((i % 3) == 0)
			{
				next_pos.x = grid_pos.x;
				next_pos.y += block_size.y + spacing;
			}
		}
	}

	O.loadFromFile("O.png");
	eks.loadFromFile("eks.png");

	turn_font.loadFromFile("arial.ttf");
	turn_text.setFont(turn_font);
	turn_text.setString(turn);
	turn_text.setCharacterSize(24);
	turn_text.setFillColor(sf::Color::White);
	turn_text.setStyle(sf::Text::Bold | sf::Text::Underlined);
}

void gui::updateTextures()
{
	for (int i = 0; i < std::size(grid); i++)
	{
		for (int j = 0; j < std::size(grid[i]); j++)
		{
			if (grid[i][j] == 'X')
			{
				blocks[i][j].setTexture(&eks, true);
			}
			else if (grid[i][j] == 'O')
			{
				blocks[i][j].setTexture(&O, true);
			}
			else
			{
				blocks[i][j].setTexture(NULL, true);
			}
		}
	}
}

void gui::draw()
{
	window.draw(turn_text);
	for (auto & row : blocks)
	{
		for (auto & b : row)
		{
			window.draw(b);
		}
	}
}

void gui::handle_event(sf::Event event)
{
	if (event.type == event.MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left)
	{
		auto mouse_pos = sf::Vector2f(sf::Mouse::getPosition(window));
		for (int i = 0; i < std::size(grid); i++)
		{
			for (int j = 0; j < std::size(grid[i]); j++)
			{
				if (blocks[i][j].getGlobalBounds().contains(mouse_pos) && grid[i][j] == NULL)
				{
					if (grid[i][j] != NULL)
					{
						return;
					}

					command *c;
					if (turn == 'X')
					{
						c = new Xcommand(j, i);
					}
					else if (turn == 'O')
					{
						c = new Ocommand(j, i);
					}

					c->execute(grid, turn);
					updateTextures();
					turn_text.setString(turn);
					list_of_commands.push_back(c);

					break;
				}
			}
		}
		char c = check_win_condition();
		if (c != NULL)
		{
			std::cout << c << " wins! " << std::endl;
			list_of_commands.clear();
			replay();
			updateTextures();
		}

		if (check_game_over())
		{
			std::cout << "It's a tie!" << std::endl;
			list_of_commands.clear();
			replay();
			updateTextures();
			turn_text.setString(turn);
			return;
		}
	}
	else if (event.type == event.KeyReleased && event.key.code == sf::Keyboard::Left)
	{
		if (!list_of_commands.empty())
		{
			list_of_commands.pop_back();
		}
		replay();
		updateTextures();
		turn_text.setString(turn);
	}
}