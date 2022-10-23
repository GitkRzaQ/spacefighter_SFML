#ifndef GAME_
#define GAME_
// sfml
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
// other
#include <string>
#include <map>
#include <iostream>

class Game
{
public:
    Game();
    void run();

private:
    void processEvents();
    void handlePlayerInput(sf::Keyboard::Key key, bool isPressed);
    void update(sf::Time deltaTime);
    void render();

private:
    sf::RenderWindow mWindow;
    sf::Sprite mPlayer;

    bool mIsMovingUp;
    bool mIsMovingDown;
    bool mIsMovingLeft;
    bool mIsMovingRight;
};

#endif // GAME_