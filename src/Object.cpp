#include <Object.hpp>
#include <Random.hpp>

#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Texture.hpp>

Object::Object(const sf::Texture& texture)
    : GameObject(texture), circle(Random::Get().Range(5.0f, 100.0f))
{
    circle.setFillColor({ 255, 0, 0, 100 });
    circle.setOrigin({ circle.getRadius(), circle.getRadius() });

    setOrigin((sf::Vector2f)(texture.getSize()) / 2.0f);
}

Object::~Object() {}

void Object::Update(float deltaTime)
{
    velocity += sf::Vector2f(
        Random::Get().Range(-2.0f, 0.0f) + 1.0f,
        Random::Get().Range(-2.0f, 0.0f) + 1.0f
    ) * speed;

    move(velocity * deltaTime);

    circle.setPosition(getPosition());
}

void Object::HitXBounds()
{
    velocity.x = -velocity.x;
}

void Object::HitYBounds()
{
    velocity.y = -velocity.y;
}

void Object::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    //target.draw(circle);
    target.draw((sf::Sprite)(*this));
}
