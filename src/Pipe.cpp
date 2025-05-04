#include <Pipe.hpp>
#include <Random.hpp>

#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Texture.hpp>

float Pipe::speed = 300.0f;

Pipe::Pipe(const sf::Texture& texture)
    : GameObject(texture)
{
    setOrigin((sf::Vector2f)(texture.getSize()) / 2.0f);
}

Pipe::~Pipe() {}

void Pipe::Update(float deltaTime)
{
    move(sf::Vector2f(-speed, 0.0f) * deltaTime);
}

void Pipe::SetIsScored(bool scored)
{
    this->scored = scored;
}

bool Pipe::IsScored()
{
    return scored;
}

void Pipe::SetSpeed(float speed)
{
    Pipe::speed = speed;
}

void Pipe::IncreaseSpeed(float speed)
{
    Pipe::speed += speed;
}

float Pipe::GetSpeed()
{
    return speed;
}
