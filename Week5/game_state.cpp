#include "game_state.h"

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