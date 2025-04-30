#include <Pipe.hpp>
#include <Random.hpp>

#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Texture.hpp>

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
