#pragma once
#include "VisibleGameObject.h"
#include <cassert>

class PlayerPaddle : public VisibleGameObject
{
public:
    PlayerPaddle();
    ~PlayerPaddle();

    void Update(float elapsedTime);
    void Draw(sf::RenderWindow& window);

    float GetVelocity() const;

private:
    float _velocity; // -- left ++ right
    float _maxVelocity;
};