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
            Random::Get().Range(50.0f, window->getSize().y)
        });
        object->setScale({ 0.05f, 0.05f });

        objects.push_back(std::move(object));
    }
}

void Game::PollEvent(const std::optional<sf::Event>& event) {}

void Game::Update(float deltaTime)
{
    ProcessInput();

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

void Game::ProcessCollision(ObjectPtr& object)
{
    CheckScreenBounds(object);
    CheckObjectBounds(object);
}

void Game::ProcessInput()
{
    if(sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
    {
        auto object = std::make_unique<Object>(texture);

        object->setPosition((sf::Vector2f)(sf::Mouse::getPosition(*window)));
        object->setScale({ 0.05f, 0.05f });

        objects.push_back(std::move(object));
    }
}

void Game::CheckScreenBounds(ObjectPtr& object)
{
    auto leftEdge = object->getPosition().x - object->getGlobalBounds().size.x / 2.0f;
    auto rightEdge = object->getPosition().x + object->getGlobalBounds().size.x / 2.0f;

    auto topEdge = object->getPosition().y - object->getGlobalBounds().size.y / 2.0f;
    auto bottomEdge = object->getPosition().y + object->getGlobalBounds().size.y / 2.0f;

    if(leftEdge < 0.0f || rightEdge > window->getSize().x)
    {
        object->HitXBounds();

        if(leftEdge < 0.0f)
            object->move({ 0.0f - leftEdge, 0.0f });
        else if(rightEdge > window->getSize().x)
            object->move({ window->getSize().x - rightEdge, 0.0f });
    }

    if(topEdge < 0.0f || bottomEdge > window->getSize().y)
    {
        object->HitYBounds();

        if(topEdge < 0.0f)
            object->move({ 0.0f, 0.0f - topEdge });
        else if(bottomEdge > window->getSize().y)
            object->move({ 0.0f, window->getSize().y - bottomEdge });
    }
}

void Game::CheckObjectBounds(ObjectPtr& object)
{
    for(auto& i : objects)
        if(object != i && (object->getPosition() - i->getPosition()).length() < 50.0f)
        {
            auto intersection = object->getGlobalBounds().findIntersection(i->getGlobalBounds());
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
