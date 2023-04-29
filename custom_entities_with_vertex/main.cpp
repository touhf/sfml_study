#include <SFML/Graphics.hpp>
#include <stdio.h>

int main()
{
	sf::ContextSettings settings;
	settings.antialiasingLevel = 8;

	// create window
	sf::RenderWindow window(sf::VideoMode(800, 600), "first window",
									sf::Style::Default, settings);

	sf::VertexArray triangle(sf::Triangles, 3);

	triangle[0].position = sf::Vector2f(110.f, 10.f);
	triangle[1].position = sf::Vector2f(250.f, 10.f);
	triangle[2].position = sf::Vector2f(190.f, 120.f);

	triangle[0].color = sf::Color::Red;
	triangle[1].color = sf::Color::Magenta;
	triangle[2].color = sf::Color::Yellow;

	// create a quad
	sf::VertexArray quad(sf::Quads, 4);

	// define it as a rectangle, located at (10, 10) and with size 100x100
	quad[0].position = sf::Vector2f(10.f, 10.f);
	quad[1].position = sf::Vector2f(110.f, 10.f);
	quad[2].position = sf::Vector2f(110.f, 110.f);
	quad[3].position = sf::Vector2f(10.f, 110.f);

	// define its texture area to be a 25x50 rectangle starting at (0, 0)
	quad[0].texCoords = sf::Vector2f(0.f, 0.f);
	quad[1].texCoords = sf::Vector2f(25.f, 0.f);
	quad[2].texCoords = sf::Vector2f(25.f, 50.f);
	quad[3].texCoords = sf::Vector2f(0.f, 50.f);

	sf::Texture texture;
	if (!texture.loadFromFile("./image.png"))
	{
		printf("couldn't load texture\n");
	}

	sf::RenderStates states;
	states.texture = &texture;

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		window.draw(triangle);
		window.draw(quad, states);

		window.display();
	}
	return 0;
}

	
