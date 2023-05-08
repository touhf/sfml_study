#pragma once
#include "SFML/Window.hpp"
#include "SFML/Graphics.hpp"
#include "MainMenu.h"
#include "SplashScreen.h"
#include "PlayerPaddle.h"
#include "GameObjectManager.h"
#include "GameBall.h"

class Game
{
public:
    static void Start();
    static sf::RenderWindow& GetWindow();
    const static sf::Input& GetInput();
    const static int SCREEN_WIDTH = 1024;
    const static int SCREEN_HEIGHT = 768;

private:
    static bool isExiting();
    static void GameLoop();

    static void ShowSplashScreen();
    static void ShowMenu();

    enum GameState { Uninitialized, ShowingSplash, Paused, 
                    ShowingMenu, Playing, Exiting };

    static GameState _gameState;
    static sf::RenderWindow _mainWindow;

    static GameObjectManager _gameObjectManager;
};