#include <GameObject.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Texture.hpp>

GameObject::GameObject(const sf::Texture& texture)
    : Sprite(texture)
{}

GameObject::~GameObject() = default;
