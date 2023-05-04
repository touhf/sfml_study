#include "Game.h"

void Game::Start(void)
{
    if (_gameState != Uninitialized)
        return;
    
    _mainWindow.create(sf::VideoMode(1024, 768, 32), "Pang!");
    _gameState = Game::ShowingSplash;

    while (!isExiting())
    {
        GameLoop();
    }

    _mainWindow.close();
}

bool Game::isExiting()
{
    if (_gameState == Game::Exiting)
        return true;
    else
        return false;
}

void Game::GameLoop()
{
    sf::Event currentEvent;
    while (_mainWindow.isOpen())
    {
        while (_mainWindow.pollEvent(currentEvent))
        {
            switch (_gameState)
            {
                case Game::Playing:
                {
                    _mainWindow.clear(sf::Color(0,0,0));
                    _mainWindow.display();

                    if (currentEvent.type == sf::Event::Closed)
                    {
                        _gameState = Game::Exiting;
                    }

                    if (currentEvent.type == sf::Event::KeyPressed)
                    {
                        //if (currentEvent.Key.Code == sf::Keyboard::Escape)
                        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
                            ShowMenu();
                    }

                    break;
                }

                case Game::ShowingMenu:
                {
                    ShowMenu();
                    break;
                }

                case Game::ShowingSplash:
                {
                    ShowSplashScreen();
                    break;
                }
            }
        }
    }
}

void Game::ShowSplashScreen()
{
    SplashScreen splashScreen;
    splashScreen.Show(_mainWindow);
    _gameState = Game::ShowingMenu;
}

void Game::ShowMenu()
{
    MainMenu mainMenu;
    MainMenu::MenuResult result = mainMenu.Show(_mainWindow);
    switch (result)
    {
    case MainMenu::Exit:
        _gameState = Game::Exiting;
        break;
    case MainMenu::Play:
        _gameState = Game::Playing;
        break;
    }
}

Game::GameState Game::_gameState = Uninitialized;
sf::RenderWindow Game::_mainWindow;