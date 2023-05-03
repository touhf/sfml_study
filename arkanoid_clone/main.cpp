#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

using namespace std;
using namespace sf;

// constexpr - immutable compile-time value
constexpr int windowWidth {800}, windowHeight {600};
constexpr float ballRadius {10.f}, ballVelocity {8.f};
constexpr float paddleWidth {60.f}, paddleHeight {20.f}, paddleVelocity {6.f};

// constants for bricks
constexpr float blockWidth {60.f}, blockHeight {20.f};
constexpr int countBlocksX {11}, countBlocksY {4};

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

    void update() 
    { 
        shape.move(velocity); 

        // keeping ball inside the screen
        if (left() < 0) velocity.x = ballVelocity;
        else if (right() > windowWidth) velocity.x = -ballVelocity;
        
        if (top() < 0) velocity.y = ballVelocity;
        else if (bottom() > windowHeight) velocity.y = -ballVelocity;
    }

    float x() { return shape.getPosition().x; }
    float y() { return shape.getPosition().y; }
    float left()   { return x() - shape.getRadius(); }
    float right()  { return x() + shape.getRadius(); }
    float top()    { return y() - shape.getRadius(); }
    float bottom() { return y() + shape.getRadius(); }
};

struct Paddle
{
    RectangleShape shape;
    Vector2f velocity;

    Paddle(float mX, float mY)
    {
        shape.setPosition(mX, mY);
        shape.setSize({paddleWidth, paddleHeight});
        shape.setFillColor(Color::White);
        shape.setOrigin(paddleWidth / 2.f, paddleHeight / 2.f);
    }

    void update()
    {
        shape.move(velocity);

        // moving and keeping paddle inside window
        if (Keyboard::isKeyPressed(Keyboard::Key::Left) &&
                left() > 0) velocity.x = -paddleVelocity;
        else if (Keyboard::isKeyPressed(Keyboard::Key::Right) &&
                right() < windowWidth) velocity.x = paddleVelocity;
        
        // if no input staying in one place
        else velocity.x = 0;
    }

    float x() { return shape.getPosition().x; }
    float y() { return shape.getPosition().y; }
    float left()   { return x() - shape.getSize().x / 2.f; }
    float right()  { return x() + shape.getSize().x / 2.f; }
    float top()    { return y() - shape.getSize().y / 2.f; }
    float bottom() { return y() + shape.getSize().y / 2.f; }
};

struct Brick
{
    RectangleShape shape;

    bool destroyed {false};

    Brick (float mX, float mY)
    {
        shape.setPosition(mX, mY);
        shape.setSize({blockWidth, blockHeight});
        shape.setFillColor(Color::Yellow);
        shape.setOrigin(blockWidth / 2.f, blockHeight / 2.f);
    }

    float x() { return shape.getPosition().x; }
    float y() { return shape.getPosition().y; }
    float left()   { return x() - shape.getSize().x / 2.f; }
    float right()  { return x() + shape.getSize().x / 2.f; }
    float top()    { return y() - shape.getSize().y / 2.f; }
    float bottom() { return y() + shape.getSize().y / 2.f; }
};

// generic function to check collision between two shapes
template<class T1, class T2> bool isIntersecting(T1& mA, T2& mB)
{
    return mA.right() >= mB.left() && mA.left() <= mB.right()
            && mA.bottom() >= mB.top() && mA.top() <= mB.bottom();
}

void checkCollision(Paddle& mPaddle, Ball& mBall)
{
    // if no intersection return
    if (!isIntersecting(mPaddle, mBall)) return;

    // otherwise push ball upwards
    mBall.velocity.y = -ballVelocity;

    if (mBall.x() < mPaddle.x()) mBall.velocity.x = -ballVelocity;
    else mBall.velocity.x = ballVelocity;
}

void checkCollision(Brick& mBrick, Ball& mBall)
{
    // if no collision return
    if (!isIntersecting(mBrick, mBall)) return;

    // otherwise brick got hit
    mBrick.destroyed = true;

    // calculating how much ball intersects the brick in every direction
    float overlapLeft   {mBall.right() - mBrick.left()};
    float overlapRight  {mBrick.right() - mBrick.left()};
    float overlapTop    {mBall.bottom() - mBrick.top()};
    float overlapBottom {mBrick.bottom() - mBall.top()};

    // if megnitude of the left overlap is smaller than the right we can assume
    // the ball hit brick from the left etc...
    bool ballFromLeft(abs(overlapLeft) < abs(overlapRight));
    bool ballFromTop(abs(overlapTop) < abs(overlapBottom));

    // let's store the miniumum overlaps for the X and Y axes
    float minOverlapX {ballFromLeft ? overlapLeft : overlapRight};
    float minOverlapY {ballFromTop ? overlapTop : overlapBottom};
    
    // if the magnitude of the X overlap is less than the magnitude
    // of the Y ovelap we can assume the ball hit the brick
    // horizontally - otherwise vertically

    // change ball velocity based on calcs above
    if (abs(minOverlapX) < abs(minOverlapY))
        mBall.velocity.x = ballFromLeft ? -ballVelocity : ballVelocity;
    else
        mBall.velocity.y = ballFromTop ? -ballVelocity : ballVelocity;
}

int main()
{
    RenderWindow window {{windowWidth, windowHeight}, "Arkanoid - 1"};
    window.setFramerateLimit(60);

    Ball ball{windowWidth/2, windowHeight/2};
    Paddle paddle {windowWidth/2, windowHeight - 50};

    vector<Brick> bricks;

    // filling bricks
    for (int iX {0}; iX < countBlocksX; ++iX)
        for (int iY {0}; iY < countBlocksY; ++iY)
            bricks.emplace_back((iX + 1) * (blockWidth + 3) + 22,
                                (iY + 2) * (blockHeight + 3));

    while (window.isOpen())
    {
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
                window.close();
        }
        // clear window from previously drawn graphics
        window.clear(Color::Black);

        ball.update();
        paddle.update();

        checkCollision(paddle, ball);

        window.draw(ball.shape);
        window.draw(paddle.shape);

        // drawing bricks
        for (auto& brick : bricks) window.draw(brick.shape);

        // checking ball and brick collisions (for each brick)
        for (auto& brick : bricks) checkCollision(brick, ball);

        // removing destroyed bricks
        bricks.erase(remove_if(begin(bricks), end(bricks),
                    [](const Brick& mBrick) { return mBrick.destroyed; }),
                    end(bricks));
    
        window.display();
    }
}