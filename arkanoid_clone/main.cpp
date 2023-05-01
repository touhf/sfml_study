#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

using namespace std;
using namespace sf;

// constexpr - immutable compile-time value
constexpr int windowWidth {800}, windowHeight {600};

int main()
{
    RenderWindow window {{windowWidth, windowHeight}, "Arkanoid - 1"};
    window.setFrameLimit(60);

    while (true)
    {
        // clear window from previously drawn graphics
        window.clear(Color::Black);

        if (Keyboard::isKeyPressed(Keyboard::Key::Escape)) break;

        // show the window contents
        window.display();
    }
}