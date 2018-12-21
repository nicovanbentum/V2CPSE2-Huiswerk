#pragma once
#include "cl_state.h"

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
		c = new Xcommand(y - 1, x - 1);
	}
	else if (turn == 'O')
	{
		c = new Ocommand(y - 1, x - 1);
	}

	c->execute(grid, turn);
	list_of_commands.push_back(c);

	auto w_c = check_win_condition();
	if (w_c != NULL)
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