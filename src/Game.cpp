#include <Game.hpp>
#include <Random.hpp>

#include <print>

Game::Game(const sf::VideoMode& mode, const std::string& name)
    : Application(mode, name)
{
    if(!texture.loadFromFile("../resources/textures/ptitsa.png"))
        std::println("Failed to load texture");

    if(!texture.generateMipmap())
        std::println("Failed to generate mipmap");

    for(int i = 0; i < 200; i++)
    {
        auto object = std::make_unique<Object>(texture);

        object->setPosition({
            Random::Get().Range(0.0f, window->getSize().x),
            Random::Get().Range(0.0f, window->getSize().y)
        });
        object->setScale({ 0.05f, 0.05f });

        objects.push_back(std::move(object));
    }
}

void Game::PollEvent(const std::optional<sf::Event>& event) {}

void Game::Update(float deltaTime)
{
    for(auto& i : objects)
    {
        i->Update(deltaTime);

        if(i->getPosition().x < 0.0f || i->getPosition().x > window->getSize().x)
        {
            i->HitXBounds();

            if(i->getPosition().x < 0.0f)
                i->move({ 0.0f - i->getPosition().x, 0.0f });
            else
                i->move({ window->getSize().x - i->getPosition().x, 0.0f });
        }
        if(i->getPosition().y < 0.0f || i->getPosition().y > window->getSize().y)
        {
            i->HitYBounds();

            if(i->getPosition().y < 0.0f)
                i->move({ 0.0f, 0.0f - i->getPosition().y });
            else
                i->move({ 0.0f, window->getSize().y - i->getPosition().y });
        }

        for(auto& j : objects)
            if(i != j && (i->getPosition() - j->getPosition()).length() < 50.0f)
            {
                auto intersection = i->getGlobalBounds().findIntersection(j->getGlobalBounds());
                if(intersection.has_value())
                {
                    if(intersection.value().size.x < intersection.value().size.y)
                    {
                        i->HitXBounds();
                        i->move({ -intersection.value().size.x, 0.0f });
                    }
                    else
                    {
                        i->HitYBounds();
                        i->move({ 0.0f, -intersection.value().size.y });
                    }
                }
            }
    }
}

void Game::Render()
{
    window->clear({ 200, 255, 200 });

    for(auto& i : objects)
        window->draw(*i);
}
