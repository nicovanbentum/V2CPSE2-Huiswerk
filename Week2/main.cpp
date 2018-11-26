#include <iostream>
#include <functional>
#include <SFML/Graphics.hpp>
#include "objects.hpp"

class action {
private:
	std::function< bool() > condition;
	std::function< void() > work;
public:
	action(
		bool b,
		std::function< void() > work
	) :
		condition(
			[&b]()->bool { return b; }
		),
		work(work)
	{}

	action(
	   std::function< bool() > condition, 
	   std::function< void() > work
	) : condition( condition ), 
		work( work ) 
	{}

	action(
		sf::Keyboard::Key key,
		std::function< void() > work
	) :
		condition(
			[ key ]()->bool { return sf::Keyboard::isKeyPressed( key ); }
		),
		work(work)
	{}

	action(
		sf::Mouse::Button button,
		std::function< void() > work
	) :
		condition(
			[ button ]()->bool { return sf::Mouse::isButtonPressed( button ); }
		),
		work(work)
	{}

	void operator()(){
		if( condition() ){
			work();
		}
	}
};

int main( int argc, char *argv[] ){
	std::cout << "Starting application 01-05 array of actions\n";

	sf::RenderWindow window{ sf::VideoMode{ 640, 480 }, "SFML window" };
	ball my_ball{ sf::Vector2f{ 320.0, 240.0 }, 30, sf::Vector2f(0, 5) };
	walls my_walls(sf::Vector2f(5, 5), sf::Vector2f(620, 460), 5);
	square my_square(sf::Vector2f(20, 20), sf::Vector2f(100, 15));

	action actions[] = {
		action([&]()->bool { return my_ball.overlaps(my_walls); }, 
				[&](){ my_ball.speed.y = my_ball.speed.y * -1; })
				,
		action([&]()->bool { return my_ball.overlaps(my_square); }, 
				[&](){ my_ball.speed.y = my_ball.speed.y * -1; })
				,
		action(true, [&]() {my_ball.move(sf::Vector2f(my_ball.speed.x, my_ball.speed.y)); }),
		action( sf::Keyboard::A,  [&](){ my_square.move( sf::Vector2f( -5.0,  0.0 )); }),
		action( sf::Keyboard::D, [&](){ my_square.move( sf::Vector2f( +5.0,  0.0 )); }),
		action( sf::Keyboard::W,    [&](){ my_square.move( sf::Vector2f(  0.0, -5.0 )); }),
		action( sf::Keyboard::S,  [&](){ my_square.move( sf::Vector2f(  0.0, +5.0 )); }),
		action( sf::Mouse::Left,     [&](){ my_ball.jump( sf::Mouse::getPosition( window )); })
	};

	while (window.isOpen()) {
		for( auto & action : actions ){
			action();
		}

		window.clear();
		my_ball.draw( window );
		my_walls.draw(window);
		my_square.draw(window);
		window.display();

		sf::sleep( sf::milliseconds( 20 ));

        sf::Event event;		
	    while( window.pollEvent(event) ){
			if( event.type == sf::Event::Closed ){
				window.close();
			}
		}	
	}

	std::cout << "Terminating application\n";
	return 0;
}

