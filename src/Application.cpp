#include <Application.hpp>

Application::Application(const sf::VideoMode& mode, const std::string& name)
{
    sf::ContextSettings settings;
    settings.antiAliasingLevel = 4;

    window = std::make_unique<sf::RenderWindow>(mode, name, sf::Style::Default, sf::State::Windowed, settings);
}

Application::~Application()
{
    window->close();
}

void Application::Run()
{
    running = true;

    sf::Clock clock;

    while(running)
    {
        PollEvents();

        Update(clock.restart().asSeconds());

        Render();

        window->display();
    }
}

void Application::PollEvents()
{
    while(const auto& event = window->pollEvent())
    {
        if(event->is<sf::Event::Closed>())
            running = false;
        else
            PollEvent(event);
    }
}
