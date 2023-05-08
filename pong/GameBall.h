#pragma once
#include "SFML/Window.hpp"
#include "SFML/Graphics.hpp"
#include "VisibleGameObject.h"
#include <cassert>

class GameBall : public VisibleGameObject
{
public:
    GameBall();
    virtual ~GameBall();
};