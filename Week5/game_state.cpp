#include "game_state.h"

void tic_tac_toe::replay()
{
	for (auto & row : grid)
	{
		for (auto & val : row)
		{
			val = turns::NONE;
		}
	}

	turn = turns::X;
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
			if (b == turns::NONE)
			{
				no_null = false;
			}
		}
	}

	return no_null;

}

turns tic_tac_toe::check_win_condition()
{
	for (int i = 0; i < 3; i++)
	{
		if ( (grid[i][0] == grid[i][1]) &&
			 (grid[i][1] == grid[i][2]) &&
			 (grid[i][2] != turns::NONE))
		{
			return grid[i][2];
		}

		if ((grid[0][i] == grid[1][i]) &&
			(grid[1][i] == grid[2][i]) &&
			(grid[2][i] != turns::NONE))
		{
			return grid[2][i];
		}

	}

	if ((grid[0][0] == grid[1][1]) &&
		(grid[1][1] == grid[2][2]) &&
		(grid[1][1] != turns::NONE))
	{
		return grid[1][1];
	}

	if ((grid[0][2] == grid[1][1]) &&
		(grid[1][1] == grid[2][0]) &&
		(grid[1][1] != turns::NONE))
	{
		return grid[1][1];
	}

	return turns::NONE;
}

char tic_tac_toe::get_turn_text()
{
	return static_cast<char>(turn);
}