#include "objects.hpp"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>
#include <vector>

struct unknown_object_type : public std::exception
{
	std::string return_text;

	unknown_object_type(const std::string & text, int line)
	{
		return_text = "Exception thrown at line " + std::to_string(line) + " in file " + __FILE__ ", Found unknown object in config file of type: " + text;
	}
	const char * what() const override
	{
		return return_text.c_str();
	}
};

std::vector<std::string> split_string_to_vector(std::string & s, char delimiter)
{
	std::string name = "";
	std::vector<std::string> vec = {};
	for (int i = 0; i < s.length(); i++)
	{
		if (s[i] != delimiter)
		{
			name += s[i];
			continue;
		}
		else
		{
			vec.push_back(name);
			name = "";
		}
	}
	return vec;
}

drawable * vector_to_object(std::vector<std::string> object_data)
{
	std::string name = object_data[0];
	float posx = std::stof(object_data[1]);
	float posy = std::stof(object_data[2]);

	if (name == "RECTANGLE")
	{
		float sizex = std::stof(object_data[3]);
		float sizey = std::stof(object_data[4]);

		return new rectangle(sf::Vector2f(posx, posy), sf::Vector2f(sizex, sizey));
	}
	else if (name == "BALL")
	{
		float size = std::stof(object_data[3]);
		return new ball(sf::Vector2f(posx, posy), size);
	}
	else if (name == "LINE")
	{
		float length = std::stof(object_data[3]);
		float thickness = std::stof(object_data[4]);
		return new line(sf::Vector2f(posx, posy), length, thickness);
	}
	else if (name == "PICTURE")
	{
		float sizex = std::stof(object_data[3]);
		float sizey = std::stof(object_data[4]);
		return new picture("sprite.png", sf::Vector2f(posx, posy), sf::Vector2f(sizex, sizey));
	}
	else
	{
		throw unknown_object_type(name, __LINE__);
	}
}

std::vector<drawable*> file_to_vector_of_objects(std::ifstream & ifs)
{
	std::string input = "";
	std::vector<drawable*> return_vector;

	if (ifs.is_open())
	{
		while (getline(ifs, input))
		{
			auto object_vector = split_string_to_vector(input, ';');

			drawable * obj;
			try
			{
				obj = vector_to_object(object_vector);
				return_vector.push_back(obj);
			}
			catch (const std::exception & e)
			{
				std::cerr << e.what();
			}
			
			input = "";
		}

		return return_vector;
	}
	else
	{
		std::cout << "file not open";
	}
}

void vector_of_objects_to_file(std::vector<drawable*> & objects, std::ofstream & ofs)
{
	for (auto & obj : objects)
	{
		int posx = obj->Body().getPosition().x;
		int posy = obj->Body().getPosition().y;

		if (obj->id == "RECTANGLE")
		{
			int sizex = obj->getSize().x;
			int sizey = obj->getSize().y;
			std::string output = obj->id
				+ ";" + std::to_string(posx)
				+ ";" + std::to_string(posy)
				+ ";" + std::to_string(sizex)
				+ ";" + std::to_string(sizey)
				+ ";" + "\n";
				ofs << output;
		}
		else if (obj->id == "LINE")
		{
			int sizex = obj->getSize().x;
			int sizey = obj->getSize().y;
			std::string output = obj->id 
				+ ";" + std::to_string(posx)
				+ ";" + std::to_string(posy)
				+ ";" + std::to_string(sizex)
				+ ";" + std::to_string(sizey)
				+ ";" + "\n";
			ofs << output;
		}
		else if (obj->id == "BALL")
		{
			int radius = obj->getSize().x;
			std::string output = obj->id 
				+ ";" + std::to_string(posx)
				+ ";" + std::to_string(posy)
				+ ";" + std::to_string(radius)
				+ ";" + "\n";
			ofs << output;
		}
		else if (obj->id == "PICTURE")
		{
			int sizex = obj->getSize().x;
			int sizey = obj->getSize().y;
			std::string output = obj->id
				+ ";" + std::to_string(posx)
				+ ";" + std::to_string(posy)
				+ ";" + std::to_string(sizex)
				+ ";" + std::to_string(sizey)
				+ ";" + obj->texture_location
				+ ";" + "\n";
			ofs << output;
		}
		else
		{
			continue;
		}
	}
}

int main(int argc, char *argv[]) {
	std::cout << "starting.." << std::endl;

	sf::RenderWindow window{ sf::VideoMode{1280, 720}, "SFML window" };

	std::ifstream ifs("config.txt");
	
	auto game_objects = file_to_vector_of_objects(ifs);

	sf::Clock delta_clock;
	float dt = 0;

	while (window.isOpen()) {
		dt = delta_clock.restart().asSeconds();

		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			auto mouse_pos = sf::Vector2f(sf::Mouse::getPosition(window));
			for (auto & obj : game_objects)
			{
				if (obj->isSelected)
				{
					obj->Body().setPosition(mouse_pos);
					break;
				}

				if (obj->Body().getGlobalBounds().contains(mouse_pos))
				{
					obj->isSelected = true;
					obj->Body().setOutlineColor(sf::Color::Red);
					obj->Body().setOutlineThickness(3);
				}
			}
		}

		if (sf::Mouse::isButtonPressed(sf::Mouse::Right))
		{
			for (auto & obj : game_objects)
			{
				obj->isSelected = false;
				obj->Body().setOutlineThickness(0);
			}
		}

		window.clear();

		for (auto & obj : game_objects)
		{
			obj->draw(window);
		}

		window.display();

		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				std::ofstream ofs("config.txt");
				if (ofs.is_open()) vector_of_objects_to_file(game_objects, ofs);
				ofs.close();
				window.close();
			}
		}
	}
	std::cout << "Terminating application\n";
	return 0;
}

