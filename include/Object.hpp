#pragma once
#include <SFML/Graphics/CircleShape.hpp>

#include <GameObject.hpp>

#include <memory>

class Object : public GameObject
{
public:
    Object(const sf::Texture& texture);
    ~Object();

    void Update(float deltaTime) override;
    
    void HitXBounds();
    void HitYBounds();

    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

private:
    float speed = 1.0f;

    sf::Vector2f velocity;

    sf::CircleShape circle;
};

using ObjectPtr = std::unique_ptr<Object>;
