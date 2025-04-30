#pragma once
#include <SFML/Graphics.hpp>

#include <string>

class Application
{
public:
    Application(const sf::VideoMode& mode, const std::string& name);
    virtual ~Application();

    void Run();

protected:
    virtual void PollEvent(const std::optional<sf::Event>& event) = 0;
    void PollEvents();

    virtual void Update(float deltaTime) = 0;

    virtual void Render() = 0;

protected:
    bool running;

    std::unique_ptr<sf::RenderWindow> window;
};
