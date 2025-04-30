#pragma once
#include <Application.hpp>
#include <Object.hpp>

class Game : public Application
{
public:
    Game(const sf::VideoMode& mode, const std::string& name);
    ~Game() = default;

private:
    void PollEvent(const std::optional<sf::Event>& event) override;

    void Update(float deltaTime) override;

    void Render() override;

private:
    void ProcessInput();

private:
    void ProcessCollision(std::unique_ptr<Object>& object);

    void CheckScreenBounds(std::unique_ptr<Object>& object);
    void CheckObjectBounds(std::unique_ptr<Object>& object);

private:
    sf::Texture texture;
    std::vector<ObjectPtr> objects;
};
