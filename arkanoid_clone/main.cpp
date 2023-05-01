#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

using namespace std;
using namespace sf;

// constexpr - immutable compile-time value
constexpr int windowWidth {800}, windowHeight {600};
constexpr float ballRadius {10.f};

struct Ball
{
    CircleShape shape;

    Ball(float mX, float mY)
    {
        shape.setPosition(mX, mY);
        shape.setRadius(ballRadius);
        shape.setFillColor(Color::Red);
        shape.setOrigin(ballRadius, ballRadius);
    }
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

        window.draw(ball.shape);
        // show the window contents
        window.display();
    }
}