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

        ProcessCollision(i);
    }
}

void Game::Render()
{
    window->clear({ 200, 255, 200 });

    for(auto& i : objects)
        window->draw(*i);
}

void Game::ProcessCollision(std::unique_ptr<Object>& object)
{
    CheckScreenBounds(object);
    CheckObjectBounds(object);
}

void Game::CheckScreenBounds(std::unique_ptr<Object>& object)
{
    if(object->getPosition().x < 0.0f || object->getPosition().x > window->getSize().x)
    {
        object->HitXBounds();

        if(object->getPosition().x < 0.0f)
            object->move({ 0.0f - object->getPosition().x, 0.0f });
        else
            object->move({ window->getSize().x - object->getPosition().x, 0.0f });
    }

    if(object->getPosition().y < 0.0f || object->getPosition().y > window->getSize().y)
    {
        object->HitYBounds();

        if(object->getPosition().y < 0.0f)
            object->move({ 0.0f, 0.0f - object->getPosition().y });
        else
            object->move({ 0.0f, window->getSize().y - object->getPosition().y });
    }
}

void Game::CheckObjectBounds(std::unique_ptr<Object>& object)
{
    for(auto& j : objects)
        if(object != j && (object->getPosition() - j->getPosition()).length() < 50.0f)
        {
            auto intersection = object->getGlobalBounds().findIntersection(j->getGlobalBounds());
            if(intersection.has_value())
            {
                if(intersection.value().size.x < intersection.value().size.y)
                {
                    object->HitXBounds();
                    object->move({ -intersection.value().size.x, 0.0f });
                }
                else
                {
                    object->HitYBounds();
                    object->move({ 0.0f, -intersection.value().size.y });
                }
            }
        }
}
