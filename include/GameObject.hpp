#pragma once
#include <SFML/Graphics/Sprite.hpp>

#include <memory>

class GameObject : public sf::Sprite
{
public:
    GameObject(const sf::Texture& texture);
    virtual ~GameObject();

    virtual void Update(float deltaTime) = 0;
};

using SpritePtr = std::unique_ptr<sf::Sprite>;
