#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>

class Game
{
public:
    Game() : mWindow(sf::VideoMode(800, 600), "Spacefighter"), mPlayer()
    {
        mPlayer.setRadius(25.f);
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
    void update();
    void render();

private:
    sf::RenderWindow mWindow;
    sf::CircleShape mPlayer;
};

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

        case sf::Evnet::Closed:
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

void Game::update(){};

int main()
{
    Game game;
    game.run();
}