#pragma once
#include <SFML/Graphics/CircleShape.hpp>

#include <GameObject.hpp>

#include <memory>

class Pipe : public GameObject
{
public:
    Pipe(const sf::Texture& texture);
    ~Pipe() override;

    void Update(float deltaTime) override;
    void SetIsScored(bool scored);

    bool IsScored() const;

public:
    static void SetSpeed(float speed);
    static void IncreaseSpeed(float speed);

    static float GetSpeed();

private:
    static float speed;

private:
    bool scored = false;
};

using PipePtr = std::unique_ptr<Pipe>;
