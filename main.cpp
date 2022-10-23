#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>

class Game
{
public:
    Game() : mWindow(sf::VideoMode(800, 600), "Spacefighter"), mPlayer()
    {
        mPlayer.setRadius(5.f);
        mPlayer.setPosition(150.f, 150.f);
        mPlayer.setFillColor(sf::Color::Red);
    }

    void run()
    {
        while (mWindow.isOpen())
        {
            processEvents();
            update();
            render();
        }
    }

private:
    void processEvents();
    void handlePlayerInput(sf::Keyboard::Key key, bool isPressed);
    void update();
    void render();

private:
    sf::RenderWindow mWindow;
    sf::CircleShape mPlayer;

    bool mIsMovingUp;
    bool mIsMovingDown;
    bool mIsMovingLeft;
    bool mIsMovingRight;
};

void Game::handlePlayerInput(sf::Keyboard::Key key, bool isPressed)
{

    if (key == sf::Keyboard::W)
        mIsMovingUp = isPressed;
    if (key == sf::Keyboard::S)
        mIsMovingDown = isPressed;
    if (key == sf::Keyboard::A)
        mIsMovingLeft = isPressed;
    if (key == sf::Keyboard::D)
        mIsMovingRight = isPressed;
}

void Game::processEvents()
{
    sf::Event event;
    while (mWindow.pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
            mWindow.close();

        switch (event.type)
        {
        case sf::Event::KeyPressed:
            handlePlayerInput(event.key.code, true);
            break;

        case sf::Event::KeyReleased:
            handlePlayerInput(event.key.code, false);
            break;

        case sf::Event::Closed:
            mWindow.close();
            break;
        }
    }
}

void Game::render()
{
    mWindow.clear();
    mWindow.draw(mPlayer);
    mWindow.display();
}

void Game::update()
{

    sf::Vector2f movement(0.f, 0.f);
    if (mIsMovingUp)
        movement.y -= 1.f;
    if (mIsMovingDown)
        movement.y += 1.f;
    if (mIsMovingLeft)
        movement.x -= 1.f;
    if (mIsMovingRight)
        movement.x += 1.f;

    mPlayer.move(movement);
}

int main()
{
    Game game;
    game.run();
}