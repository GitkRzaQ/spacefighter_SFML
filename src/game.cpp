#include "../include/game.hpp"
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
    mPlayer.setTexture(mTextures.get(Textures::Airplane));
    sf::FloatRect rect(mPlayer.getGlobalBounds());

    mPlayer.setOrigin(rect.width / 2, rect.height / 2);
    mPlayer.setScale(0.5f, 0.5f);
    mPlayer.setPosition(250.f, 150.f);
}

void Game::run()
{
    sf::Time TimePerFrame;
    TimePerFrame = sf::seconds(1.f / 60.f);
    sf::Clock clock;
    sf::Time timeSinceLastUpdate = sf::Time::Zero;

    multiplier = 10;
    movement = sf::Vector2f(0, 0);

    winsize.x = mWindow.getSize().x - 1;
    winsize.y = mWindow.getSize().y - 1;

    while (mWindow.isOpen())
    {
        timeSinceLastUpdate += clock.restart();
        while (timeSinceLastUpdate > TimePerFrame)
        {
            timeSinceLastUpdate -= TimePerFrame;
            processEvents();
            update(TimePerFrame);
            // std::cout << "winsize.y " << winsize.x
            //           << "\tPlayer.y " << mPlayer.getPosition().y
            //           << "\tTexture.y " << mPlayer.getTexture()->getSize().y << std::endl;
        }
        render();
    }
}
void Game::handlePlayerInput(sf::Keyboard::Key key, bool isPressed)
{

    if (key == sf::Keyboard::W)
    {
        mIsMovingUp = isPressed;
    }

    if (key == sf::Keyboard::S)
    {
        mIsMovingDown = isPressed;
    }

    if (key == sf::Keyboard::A)
    {
        mIsMovingLeft = isPressed;
    }
    if (key == sf::Keyboard::D)
    {
        mIsMovingRight = isPressed;
    }
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
    sf::Vector2f windowWidth(mWindow.getSize());
    // std::cout << "Window size: " << windowWidth.x << " x " << windowWidth.y << std::endl;
    mWindow.clear();
    mWindow.draw(mPlayer);
    mWindow.display();
}

void Game::update(sf::Time deltaTime)
{

    std::cout << "Player.y < 0 ? " << ((mPlayer.getPosition().y <= 0.f) ? "true" : "false")
              << "\tPlayer.y " << mPlayer.getPosition().y
              << "\tMovement.x " << movement.x
              << "\tMovement.y " << movement.y
              << "\tTexture.y " << mPlayer.getTexture()->getSize().y << std::endl;
    // if (mIsMovingUp && (mPlayer.getPosition() < winsize) && mPlayer.getPosition() != sf::Vector2f(0,0))
    if (mIsMovingUp)
    {

        mPlayer.setRotation(0);
        movement.y -= multiplier * 1.f;
    }
    // bounce of the upper wall
    if (mPlayer.getPosition().y <= 30)
    {
        movement.y = 150.f;
    }

    if (mIsMovingDown)
    {
        mPlayer.setRotation(180);
        movement.y += multiplier * 1.f;
    }
    // bounce of the down wall
    if (mPlayer.getPosition().y >= mWindow.getSize().y - 25)
    {
        movement.y = -150.f;
    }

    if (mIsMovingLeft)
    {
        mPlayer.setRotation(-90);
        movement.x -= multiplier * 1.f;
    }
    // bounce of the left wall
    if (mPlayer.getPosition().x <= 30)
    {
        movement.x = 150.f;
    }

    if (mIsMovingRight)
    {
        mPlayer.setRotation(90);
        movement.x += multiplier * 1.f;
    }
    // bounce of the right wall
    if (mPlayer.getPosition().x >= mWindow.getSize().x - 25)
    {
        movement.x = -150.f;
    }
    if (!mIsMovingUp && !mIsMovingDown && !mIsMovingLeft && !mIsMovingRight)
        movement += sf::Vector2f(-movement.x / 50, -movement.y / 50);

    mPlayer.move(movement * deltaTime.asSeconds());
}