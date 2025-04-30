#pragma once
#include <SFML/Graphics/CircleShape.hpp>

#include <GameObject.hpp>

#include <memory>

class Pipe : public GameObject
{
public:
    Pipe(const sf::Texture& texture);
    ~Pipe();

    void Update(float deltaTime) override;

private:
    float speed = 1000.0f;
};

using PipePtr = std::unique_ptr<Pipe>;
