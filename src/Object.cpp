#include <Object.hpp>
#include <Random.hpp>

#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Texture.hpp>

Object::Object(const sf::Texture& texture)
    : GameObject(texture), circle(Random::Get().Range(5.0f, 100.0f))
{
    circle.setFillColor({ 255, 0, 0, 100 });
    circle.setOrigin({ circle.getRadius(), circle.getRadius() });

    velocity.x = Random::Get().Range(-100.0f, 100.0f);

    setOrigin((sf::Vector2f)(texture.getSize()) / 2.0f);
}

Object::~Object() {}

void Object::Update(float deltaTime)
{
    velocity += sf::Vector2f(
        0.0f,
        0.98f
    ) * deltaTime * speed;

    move(velocity);

    circle.setPosition(getPosition());
}

void Object::HitXBounds()
{
    velocity.x = -velocity.x / 2.0f;
}

void Object::HitYBounds()
{
    velocity.y = -velocity.y / 1.6f;
}

void Object::ApplyForce(const sf::Vector2f& force)
{
    velocity += force;
}

void Object::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    //target.draw(circle);
    target.draw((sf::Sprite)(*this));
}
