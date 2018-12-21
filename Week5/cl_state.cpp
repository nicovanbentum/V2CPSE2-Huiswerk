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

	turns c = check_win_condition();
	if (c != turns::NONE)
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

	std::shared_ptr<command> c;
	if (turn == turns::X)
	{
		c = std::shared_ptr<Xcommand>(new Xcommand(y-1, x-1));
	}
	else if (turn == turns::O)
	{
		c = std::shared_ptr<Ocommand>(new Ocommand(y-1, x-1));
	}

	c->execute(grid, turn);
	list_of_commands.push_back(c);

	auto w_c = check_win_condition();
	if (w_c != turns::NONE)
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