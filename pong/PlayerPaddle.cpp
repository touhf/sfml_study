#include "PlayerPaddle.h"
#include "Game.h"

PlayerPaddle::PlayerPaddle() : _velocity(0), _maxVelocity (600.0f) 
{
    Load("./paddle.png");
    assert(IsLoaded());

    GetSprite().setOrigin(GetSprite().getSize().x/2, GetSprite().getSize().y/2);
}

PlayerPaddle::~PlayerPaddle() { }

void PlayerPaddle::Draw(sf::RenderWindow& rw)
{
    VisibleGameObject::Draw(rw);
}

float PlayerPaddle::GetVelocity() const
{
    return _velocity;
}

void PlayerPaddle::Update(float elapsedTime)
{
    if (Game::GetInput().IsKeyDown(sf::Key::Left))
    {
        _velocity -= 3.0f;
    }
    if (Game::GetInput().IsKeyDown(sf::Key::Right))
    {

        _velocity += 3.0f;
    }
    if (Game::GetInput().IsKeyDown(sf::Key::Down))
    {
        _velocity = 0.0f;
    }

    if (_velocity > _maxVelocity) _velocity = _maxVelocity;
    if (_velocity < -_maxVelocity) _velocity = -_maxVelocity;

    sf::Vector2f pos = this->GetPosition();

    if (pos.x < GetSprite().GetSize().x/2
        || pos.x > (Game::SCREEN_WIDTH - GetSprite().GetSize().x/2))
    {   // bounce by current velocity in opposite direction
        _velocity = -_velocity;
    }

    GetSprite().Move(_velocity * elapsedTime, 0);
}