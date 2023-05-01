#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

using namespace std;
using namespace sf;

// constexpr - immutable compile-time value
constexpr int windowWidth {800}, windowHeight {600};
constexpr float ballRadius {10.f}, ballVelocity {8.f};

struct Ball
{
    CircleShape shape;

    // 2d vector that stores the Ball's velocity
    Vector2f velocity {-ballVelocity, -ballVelocity};

    Ball(float mX, float mY)
    {
        shape.setPosition(mX, mY);
        shape.setRadius(ballRadius);
        shape.setFillColor(Color::Red);
        shape.setOrigin(ballRadius, ballRadius);
    }

    void update() { shape.move(velocity); };
};

int main()
{
    RenderWindow window {{windowWidth, windowHeight}, "Arkanoid - 1"};
    window.setFramerateLimit(60);

    Ball ball{windowWidth/2, windowHeight/2};

    while (true)
    {
        // clear window from previously drawn graphics
        window.clear(Color::Black);

        if (Keyboard::isKeyPressed(Keyboard::Key::Escape)) break;

        // every loop we need to update ball
        ball.update();

        window.draw(ball.shape);
        // show the window contents
        window.display();
    }
}