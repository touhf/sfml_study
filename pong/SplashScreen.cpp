#include "SplashScreen.h"

void SplashScreen::Show(sf::RenderWindow& renderWindow)
{
    sf::Texture image;
    if (image.loadFromFile("./SplashScreen.png") != true)
    {
        return;
    }

    //sf::Sprite sprite(image);
    sf::Sprite sprite;
    sprite.setTexture(image);

    renderWindow.draw(sprite);
    renderWindow.display();

    sf::Event event;
    while (renderWindow.isOpen())
    {
        while (renderWindow.pollEvent(event))
        {
            if (event.type == sf::Event::EventType::KeyPressed 
                || event.type == sf::Event::EventType::MouseButtonPressed
                || event.type == sf::Event::EventType::Closed)
            {
                return;
            }
        }
    }
}