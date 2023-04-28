#include <SFML/Graphics.hpp>

int main()
{
	sf::ContextSettings settings;
	settings.antialiasingLevel = 8;

	// create window
	sf::RenderWindow window(sf::VideoMode(800, 600), "first window",
								sf::Style::Default, settings);

	// triangle
	sf::CircleShape triangle(80.f, 3);
	triangle.setPosition(10.f, 10.f);
	triangle.setFillColor(sf::Color::Green);

	// square
	sf::CircleShape square(80.f, 4);
	square.setPosition(200.f, 20.f);
	square.setFillColor(sf::Color::Blue);

	// octagon
	sf::CircleShape octagon(80.f, 8);
	octagon.setPosition(400.f, 10.f);
	octagon.setFillColor(sf::Color::Magenta);

	// convex shape example
	sf::ConvexShape convex;
	// resize it to 5 points
	convex.setPointCount(5);
	// define the points
	convex.setPoint(0, sf::Vector2f(20.f, 200.f));
	convex.setPoint(1, sf::Vector2f(790.f, 210.f));
	convex.setPoint(2, sf::Vector2f(120.f, 290.f));
	convex.setPoint(3, sf::Vector2f(30.f, 300.f));
	convex.setPoint(4, sf::Vector2f(20.f, 250.f));

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		window.draw(triangle);
		window.draw(square);
		window.draw(octagon);

		window.draw(convex);

		window.display();
	}
	return 0;
}

	
