#pragma once
#include <SFML/Graphics/Sprite.hpp>

class GameObject : public sf::Sprite
{
public:
    GameObject(const sf::Texture& texture);
    virtual ~GameObject();

    virtual void Update(float deltaTime) = 0;
};
