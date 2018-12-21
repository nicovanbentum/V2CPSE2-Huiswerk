#pragma once
#include "game_state.h"

struct command_line : tic_tac_toe
{
	command_line() {}

	int x;
	int y;

	void run();
	void draw() override;
};