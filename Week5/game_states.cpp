#include "game_states.h"

void tic_tac_toe::replay()
{
	for (auto & row : grid)
	{
		for (auto & val : row)
		{
			val = NULL;
		}
	}

	turn = 'X';
	for (auto & c : list_of_commands)
	{
		c->execute(grid, turn);
	}
}

bool tic_tac_toe::check_game_over()
{
	bool no_null = true;
	for (auto & row : grid)
	{
		for (auto & b : row)
		{
			if (b == NULL)
			{
				no_null = false;
			}
		}
	}

	return no_null;

}

char tic_tac_toe::check_win_condition()
{
	for (int i = 0; i < 3; i++)
	{
		if ( (grid[i][0] == grid[i][1]) &&
			 (grid[i][1] == grid[i][2]) &&
			 (grid[i][2] != NULL))
		{
			return grid[i][2];
		}

		if ((grid[0][i] == grid[1][i]) &&
			(grid[1][i] == grid[2][i]) &&
			(grid[2][i] != NULL))
		{
			return grid[2][i];
		}

	}

	if ((grid[0][0] == grid[1][1]) &&
		(grid[1][1] == grid[2][2]) &&
		(grid[1][1] != NULL))
	{
		return grid[1][1];
	}

	if ((grid[0][2] == grid[1][1]) &&
		(grid[1][1] == grid[2][0]) &&
		(grid[1][1] != NULL))
	{
		return grid[1][1];
	}

	return NULL;
}

gui::gui(sf::RenderWindow & window, sf::Vector2f grid_pos, sf::Vector2f block_size, float spacing) : window(window) {

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

void command_line::draw()
{
	for (auto & row : grid)
	{
		std::cout << std::endl;
		for (auto & i : row)
		{
			std::cout << "|" << i << "|";
		}
	}
	std::cout << std::endl;

	char c = check_win_condition();
	if (c != NULL)
	{
		std::cout << c << " wins!" << std::endl;
		list_of_commands.clear();
		replay();
	}
}

void command_line::run()
{
	draw();
	std::cout << "Turn: " << turn << std::endl;

	//ask x pos
	std::cout << "x Position: ";
	std::cin >> x;
	if (x == -1)
	{
		std::cout << "Undid last move" << std::endl;
		list_of_commands.pop_back();
		replay();
		run();
	}

	//ask y pos
	std::cout << "Y position: ";
	std::cin >> y;
	if (x == -1)
	{
		std::cout << "Undid last move" << std::endl;
		list_of_commands.pop_back();
		replay();
		run();
	}

	command *c;
	if (turn == 'X')
	{
		c = new Xcommand(y-1, x-1);
	}
	else if (turn == 'O')
	{
		c = new Ocommand(y-1, x-1);
	}

	c->execute(grid, turn);
	list_of_commands.push_back(c);
	
	auto w_c = check_win_condition();
	if ( w_c != NULL)
	{
		std::cout << w_c << " wins!" << std::endl;
		list_of_commands.clear();
		replay();
	}
	else if (check_game_over())
	{
		std::cout << "It's a tie!" << std::endl;
		list_of_commands.clear();
		replay();
	}

	run();
}