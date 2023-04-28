#include <SFML/Graphics.hpp>
#include <stdio.h>

int main()
{
	// create window
	sf::RenderWindow window(sf::VideoMode(800, 600), "first window");

	sf::Texture texture;
	if (!texture.loadFromFile("./image.png"))
	{
		printf("couldn't load texture\n");
	}

	texture.setSmooth(true);
	
	sf::Sprite sprite;
	sprite.setTexture(texture);
	//sprite.setColor(sf::Color(0, 255, 0));

	sprite.setScale(sf::Vector2f(1.5f, 3.f)); // 

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}
		window.draw(sprite);

		window.display();
	}
	return 0;
}

	
