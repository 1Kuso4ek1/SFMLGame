#include <Bird.hpp>
#include <Random.hpp>

#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Texture.hpp>

Bird::Bird(const sf::Texture& texture)
    : GameObject(texture)
{
    setOrigin(sf::Vector2f(texture.getSize()) / 2.0f);
}

Bird::~Bird() = default;

void Bird::Update(float deltaTime)
{
    velocity += sf::Vector2f(
        0.0f,
        0.98f
    ) * deltaTime;

    move(velocity * 3000.0f * deltaTime);

    setRotation(sf::radians(std::atan2(velocity.y, 1.0f)));
}

void Bird::HitBounds()
{
    velocity.x = -velocity.x / 2.0f;
}

void Bird::HitGround()
{
    if(velocity.y > 0.0f)
        velocity = { 0.0f, 0.0f };
}

void Bird::SetVelocity(const sf::Vector2f& velocity)
{
    this->velocity = velocity;
}

void Bird::ApplyForce(const sf::Vector2f& force)
{
    velocity += force;
}

void Bird::TakeDamage(float damage)
{
    health -= damage;
}

float Bird::GetHealth() const
{
    return health;
}

bool Bird::IsAlive() const
{
    return health > 0.0f;
}
