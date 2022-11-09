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

namespace Textures
{
    enum ID
    {
        Landscape,
        Airplane,
        Missile
    };
}

class TextureHolder
{
public:
    bool load(Textures::ID id, const std::string &filename);
    sf::Texture &get(Textures::ID id);
    const sf::Texture &get(Textures::ID id) const;

private:
    std::map<Textures::ID, std::unique_ptr<sf::Texture>> mTextureMap;
};

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
    sf::Sprite spr2;
    TextureHolder mTextures;

    sf::Vector2f movement;
    sf::Vector2f winsize;
    int multiplier;

    bool mIsMovingUp;
    bool mIsMovingDown;
    bool mIsMovingLeft;
    bool mIsMovingRight;
};

#endif // GAME_