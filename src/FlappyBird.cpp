#include <FlappyBird.hpp>
#include <Bird.hpp>
#include <Random.hpp>

#include <print>

FlappyBird::FlappyBird(const sf::VideoMode& mode, const std::string& name)
    : Application(mode, name)
{
    if(!birdTexture.loadFromFile("../resources/textures/ptitsa.png"))
        std::println("Failed to load texture");

    if(!birdTexture.generateMipmap())
        std::println("Failed to generate mipmap");

    SetupGame();
}

void FlappyBird::SetupGame()
{
    pipes.clear();

    bird = std::make_unique<Bird>(birdTexture);

    bird->setPosition({ 300.0f, 400.0f });
    bird->setScale({ -0.06f, 0.06f });

    float randomY = 0.0f;

    for(int i = 0; i < 8; i++)
    {
        auto pipe = std::make_unique<Pipe>(birdTexture);

        if(i % 2 == 0)
            randomY = Random::Get().Range(-100.0f, 100.0f);

        pipe->setPosition({ 1800.0f + (int)(i / 2) * 500.0f, (i % 2 == 0 ? 700.0f : 0.0f) + randomY });

        pipe->setScale({ 0.3f, 0.6f });

        pipes.push_back(std::move(pipe));
    }
}

void FlappyBird::PollEvent(const std::optional<sf::Event>& event)
{

    if(event->is<sf::Event::MouseButtonPressed>() || event->is<sf::Event::KeyPressed>())
    {
        if(gameOver)
        {
            SetupGame();

            gameOver = false;
            gameStarted = false;

            flapTimer.restart();
        }

        if(flapTimer.getElapsedTime().asSeconds() > 0.05f)
        {
            gameStarted = true;
    
            bird->SetVelocity({ 0.0f, -0.3f });
    
            flapTimer.restart();
        }
    }
}

void FlappyBird::Update(float deltaTime)
{
    ProcessInput();
    ProcessCollision();

    if(gameStarted)
    {
        bird->Update(deltaTime);

        if(!gameOver)
            for(auto& i : pipes)
                i->Update(deltaTime);
    }
}

void FlappyBird::Render()
{
    window->clear({ 200, 255, 200 });

    window->draw(*bird);

    for(auto& i : pipes)
        window->draw(*i);
}

void FlappyBird::ProcessCollision()
{
    CheckScreenBounds();
    CheckObjectBounds();
}

void FlappyBird::ProcessInput()
{
}

void FlappyBird::CheckScreenBounds()
{
    auto topEdge = bird->getPosition().y - bird->getGlobalBounds().size.y / 2.0f;
    auto bottomEdge = bird->getPosition().y + bird->getGlobalBounds().size.y / 2.0f;

    if(topEdge < 0.0f || bottomEdge > window->getSize().y)
    {
        if(topEdge < 0.0f)
            bird->move({ 0.0f, 0.0f - topEdge });
        else if(bottomEdge > window->getSize().y)
            bird->move({ 0.0f, window->getSize().y - bottomEdge });

        bird->HitGround();
    }

    float randomY = Random::Get().Range(-100.0f, 100.0f);

    for(auto& pipe : pipes)
    {
        auto rightEdge = pipe->getPosition().x + pipe->getGlobalBounds().size.x / 2.0f;

        if(rightEdge < 0.0f)
        {
            float y = 0.0f;

            if(pipe->getPosition().y > 500.0f)
                y = 700.0f + randomY;
            else
                y = randomY;

            pipe->setPosition({ 1800.0f + pipe->getGlobalBounds().size.x / 2.0f, y });
        }
    }
}

void FlappyBird::CheckObjectBounds()
{
    for(auto& i : pipes)
    {
        auto intersection = bird->getGlobalBounds().findIntersection(i->getGlobalBounds());

        if(intersection.has_value())
        {
            if(intersection.value().size.x < intersection.value().size.y)
            {
                bird->ApplyForce({ 0.001f, 0.0f });
                bird->move({ -intersection.value().size.x, 0.0f });
            }
            else
            {
                bird->ApplyForce({ -0.001f, 0.0f });
                bird->move({ 0.0f, -intersection.value().size.y });
            }

            gameOver = true;
        }
    }
}
