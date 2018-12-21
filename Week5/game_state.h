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

#endif
