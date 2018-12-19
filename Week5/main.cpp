#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include "commands.h"
#include "game_states.h"

int main(int argc, char *argv[]) {
	std::cout << "starting.." << std::endl;

	sf::RenderWindow window{ sf::VideoMode{850, 850}, "SFML window" };
	window.setKeyRepeatEnabled(false);
	window.setFramerateLimit(60);

	gui GUI(window, sf::Vector2f(100, 100), sf::Vector2f(200, 200), 20);
	command_line cl;

	std::cout << "\nCommand line undo: enter -1 as a position." << std::endl;
	std::cout << "GUI undo: press the Left arrow on your keyboard.\n" << std::endl;

	std::cout << std::endl;
	std::cout << "Would you like to play the game on the command line? (y/n) ";
	std::string answer;
	std::cin >> answer;

	if (answer == "y")
	{
		cl.run();
	}

	while (window.isOpen()) {
		window.clear();

		GUI.draw();
		
		window.display();
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				window.close();
			}
			GUI.handle_event(event);
		}
	}
	std::cout << "Terminating application\n";
	return 0;
}

