#include "GameBall.h"

GameBall::GameBall()
{
    Load("./ball.png");
    assert(IsLoaded());

    GetSprite().SetOrigin(15, 15);
}

GameBall::~GameBall() {}