#pragma once
#include <SFML/Graphics/CircleShape.hpp>

#include <GameObject.hpp>

#include <memory>

class Bird : public GameObject
{
public:
    Bird(const sf::Texture& texture);
    ~Bird();

    void Update(float deltaTime) override;
    
    void HitBounds();
    void HitGround();

    void SetVelocity(const sf::Vector2f& velocity);
    void ApplyForce(const sf::Vector2f& force);
    
private:
    sf::Vector2f velocity;
};

using BirdPtr = std::unique_ptr<Bird>;
