#include <SFML/Graphics.hpp>
#include <stdio.h>

int main()
{
	// create window
	sf::RenderWindow window(sf::VideoMode(800, 600), "first window");

	sf::Font font;
	if (!font.loadFromFile("./BlackthornScriptTypeface.ttf"))
	{
		printf("couldn't load font\n");
	}

	sf::Text text;
	text.setFont(font);
	text.setString("Hello WORLd!1\n#$%78_!?\nthird line\n1234567890");

	text.setCharacterSize(100);
	text.setFillColor(sf::Color::Blue);
	text.setStyle(sf::Text::Bold);

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}
		// make white background
		window.clear(sf::Color::White);

		window.draw(text);

		window.display();
	}
	return 0;
}

	
