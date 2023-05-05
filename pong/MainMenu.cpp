#include "MainMenu.h"

MainMenu::MenuResult MainMenu::Show(sf::RenderWindow& window)
{
    // load menu image from file
    //sf::Image image;
    //image.loadFromFile("./mainmenu.png");
    sf::Texture image;
    if (!image.loadFromFile("./mainmenu.png"))
    {
        printf("couldn't load texture\n");
    }
    //sf::Sprite sprite(image);
    sf::Sprite sprite;
    sprite.setTexture(image);

    // setup clickable regions

    // play menu item coordinates
    MenuItem playButton;
    /*
    playButton.rect.Top = 145;
    playButton.rect.Bottom = 380;
    playButton.rect.Left = 0;
    playButton.rect.Right = 1023;
    playButton.action = Play;
    */
    playButton.rect.top = 145;
    playButton.rect.height = 235; // 380-145
    playButton.rect.left = 0;
    playButton.rect.width = 1023;
    playButton.action = Play;
    
    // exit menu item coordinates
    MenuItem exitButton;
    /*
    exitButton.rect.Left = 0;
    exitButton.rect.Right = 1023;
    exitButton.rect.Top = 383
    exitButton.rect.Bottom = 560;
    exitButton.action = Exit;
    */
    exitButton.rect.left = 0;
    exitButton.rect.width = 1023;
    exitButton.rect.top = 383;
    exitButton.rect.height = 177;
    exitButton.action = Exit;

    _menuItems.push_back(playButton);
    _menuItems.push_back(exitButton);

    window.draw(sprite);
    window.display();

    return GetMenuResponse(window);
}

MainMenu::MenuResult MainMenu::HandleClick(int x, int y)
{
    std::list<MenuItem>::iterator it;

    for (it = _menuItems.begin(); it != _menuItems.end(); it++)
    {
        sf::Rect<int> menuItemRect = (*it).rect;
        /*
        if (menuItemRect.Bottom > y
                && menuItemRect.Top < y
                && menuItemRect.Left < x
                && menuItemRect.Right > x)
        */
        if (
            // bottom
            (menuItemRect.top + menuItemRect.height) > y &&
            // top
            menuItemRect.top < y &&
            // left
            menuItemRect.left < x &&
            // right
            (menuItemRect.left + menuItemRect.width) > x)
        {
            return (*it).action;
        }
    }
    return Nothing;
}

MainMenu::MenuResult MainMenu::GetMenuResponse(sf::RenderWindow& window)
{
    sf::Event menuEvent;

    while (window.isOpen())
    {
        while (window.pollEvent(menuEvent))
        {
            if (menuEvent.type == sf::Event::MouseButtonPressed)
            {
                return HandleClick(sf::Mouse::getPosition(window).x,
                                sf::Mouse::getPosition(window).y);
            }

            if (menuEvent.type == sf::Event::Closed)
            {
                return Exit;
            }
        }
    }
}