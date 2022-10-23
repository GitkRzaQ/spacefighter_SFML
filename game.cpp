#include "game.hpp"
#include <string>
#include <map>
#include <iostream>

bool TextureHolder::load(Textures::ID id, const std::string &filename)
{
    std::cout << "Loading textures" << std::endl;
    std::unique_ptr<sf::Texture> texture(new sf::Texture);
    if (!texture->loadFromFile(filename))
    {
        std::cout << "could not load texture from " << filename << std::endl;
        return false;
    }
    else
        std::cout << "Texture " << filename << " loaded" << filename << std::endl;

    mTextureMap.insert(std::make_pair(id, std::move(texture)));
    return true;
}

sf::Texture &TextureHolder::get(Textures::ID id)
{
    auto found = mTextureMap.find(id);
    return *found->second;
}

Game::Game() : mWindow(sf::VideoMode(800, 600), "Spacefighter"), mPlayer(), spr2()
{
    mTextures.load(Textures::Airplane, "textures/ship1.png");

    // sf::Texture tx;
    // tx.loadFromFile("textures/ship1.png");
    mPlayer.setTexture(mTextures.get(Textures::Airplane));
    // mPlayer.setTexture(tx);
    mPlayer.setPosition(250.f, 150.f);
}

void Game::run()
{
    sf::Time TimePerFrame;
    TimePerFrame = sf::seconds(1.f / 60.f);
    sf::Clock clock;
    sf::Time timeSinceLastUpdate = sf::Time::Zero;

    while (mWindow.isOpen())
    {
        timeSinceLastUpdate += clock.restart();
        while (timeSinceLastUpdate > TimePerFrame)
        {
            timeSinceLastUpdate -= TimePerFrame;
            processEvents();
            update(TimePerFrame);
        }
        render();
    }
}
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

void Game::update(sf::Time deltaTime)
{
    int multiplier = 200;
    sf::Vector2f movement(0.f, 0.f);
    if (mIsMovingUp)
        movement.y -= multiplier * 1.f;
    if (mIsMovingDown)
        movement.y += multiplier * 1.f;
    if (mIsMovingLeft)
        movement.x -= multiplier * 1.f;
    if (mIsMovingRight)
        movement.x += multiplier * 1.f;

    mPlayer.move(movement * deltaTime.asSeconds());
}