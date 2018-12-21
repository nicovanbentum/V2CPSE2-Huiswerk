#include <iostream>
#include <vector>
#include "commands.h"
#include "gui_state.h"
#include "cl_state.h"

int main(int argc, char *argv[]) {
	std::cout << "starting.." << std::endl;
	
	command_line cl;

	std::cout << "\nCommand line undo: enter 0 as a position." << std::endl;
	std::cout << "GUI undo: press the Left arrow on your keyboard.\n" << std::endl;

	std::cout << std::endl;
	std::cout << "Would you like to play the game on the command line? (y/n) ";
	std::string answer;
	std::cin >> answer;

	if (answer == "y")
	{
		for (;;)
		{
			cl.run();
		}
	}
	else
	{
		gui GUI(sf::Vector2f(100, 100), sf::Vector2f(200, 200), 20);
		GUI.run();
	}

	std::cout << "Terminating application\n";
	return 0;
}

