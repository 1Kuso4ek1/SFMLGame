#include <FlappyBird.hpp>
#include <Bird.hpp>
#include <Random.hpp>

#include <print>

FlappyBird::FlappyBird(const sf::VideoMode& mode, const std::string& name)
    : Application(mode, name)
{
    if(!birdTexture.loadFromFile("resources/textures/ptitsa.png")
       || !backgroundTexture.loadFromFile("resources/textures/background.png"))
        std::println("Failed to load texture");

    if(!birdTexture.generateMipmap()
       || !backgroundTexture.generateMipmap())
        std::println("Failed to generate mipmap");

    if(!openSans.openFromFile("resources/fonts/OpenSans-Regular.ttf"))
        std::println("Failed to load font");

    background =
    {
        std::make_unique<sf::Sprite>(backgroundTexture),
        std::make_unique<sf::Sprite>(backgroundTexture)
    };

    SetupGame();
    SetupUI();
}

void FlappyBird::SetupGame()
{
    background[0]->setPosition({ 0.0f, 0.0f });
    background[0]->setScale({ 0.8f, 0.8f });

    background[1]->setPosition({ background[0]->getGlobalBounds().size.x, 0.0f });
    background[1]->setScale({ 0.8f, 0.8f });
    
    Pipe::SetSpeed(500.0f);

    score = 0;

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

        pipe->setPosition({ 1300.0f + (int)(i / 2) * 500.0f, (i % 2 == 0 ? 700.0f : 0.0f) + randomY });

        if(i % 2 == 0)
            pipe->SetIsScored(true);

        pipe->setScale({ 0.3f, 0.6f });

        pipes.push_back(std::move(pipe));
    }
}

void FlappyBird::SetupUI()
{
    healthText = std::make_unique<sf::Text>(openSans);
    healthText->setCharacterSize(20);

    healthBar = std::make_unique<sf::RectangleShape>();
    healthBar->setFillColor({ 255, 0, 0 });
    
    healthText->setPosition({ 10.0f, 10.0f });

    healthBar->setPosition({ 10.0f, 40.0f });
    healthBar->setSize({ 100.0f, 20.0f });

    scoreText = std::make_unique<sf::Text>(openSans);
    scoreText->setCharacterSize(20);
    scoreText->setPosition({ 10.0f, 70.0f });

    gameOverText = std::make_unique<sf::Text>(openSans);
    gameOverText->setCharacterSize(50);
    gameOverText->setString("Game Over!");
    gameOverText->setPosition({
        window->getSize().x / 2.0f - gameOverText->getGlobalBounds().size.x / 2.0f,
        window->getSize().y / 2.0f - gameOverText->getGlobalBounds().size.y / 2.0f
    });
    gameOverText->setFillColor({ 255, 0, 0 });
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
    ProcessCollision(deltaTime);

    if(gameStarted)
    {
        bird->Update(deltaTime);

        gameOver = !bird->IsAlive();

        if(!gameOver)
        {
            for(const auto& i : pipes)
                i->Update(deltaTime);

            for(const auto& bg : background)
            {
                bg->move({ (-Pipe::GetSpeed() / 10.0f) * deltaTime, 0.0f });
            
                if(bg->getPosition().x + bg->getGlobalBounds().size.x < 0)
                    bg->setPosition({ bg->getGlobalBounds().size.x, 0.0f });
            }
        }
    }

    float sinValue = std::abs(std::sin(flapTimer.getElapsedTime().asSeconds() * 5.0f)) / 50.0f;

    bird->setScale(sf::Vector2f(-0.06f, 0.06f) - sf::Vector2f(sinValue, sinValue));
}

void FlappyBird::Render()
{
    window->clear({ 200, 255, 200 });

    for(const auto& bg : background)
        window->draw(*bg);

    window->draw(*bird);

    for(const auto& i : pipes)
        window->draw(*i);

    healthText->setString("Health: " + std::to_string(static_cast<int>(bird->IsAlive() ? bird->GetHealth() : 0.0f)));
    healthBar->setSize({ bird->IsAlive() ? bird->GetHealth() : 0.0f, 20.0f });

    window->draw(*healthText);
    window->draw(*healthBar);

    scoreText->setString("Score: " + std::to_string(score));

    window->draw(*scoreText);

    if(gameOver)
        window->draw(*gameOverText);
}

void FlappyBird::ProcessCollision(float deltaTime)
{
    CheckScreenBounds(deltaTime);
    CheckObjectBounds(deltaTime);
}

void FlappyBird::ProcessInput()
{
}

void FlappyBird::CheckScreenBounds(float deltaTime) const
{
    auto topEdge = bird->getPosition().y - bird->getGlobalBounds().size.y / 2.0f;
    auto bottomEdge = bird->getPosition().y + bird->getGlobalBounds().size.y / 2.0f;
    auto leftEdge = bird->getPosition().x - bird->getGlobalBounds().size.x / 2.0f;

    if(topEdge < 0.0f || bottomEdge > window->getSize().y || leftEdge < 0.0f)
    {
        if(topEdge < 0.0f)
            bird->move({ 0.0f, 0.0f - topEdge });
        else if(bottomEdge > window->getSize().y)
            bird->move({ 0.0f, window->getSize().y - bottomEdge });
        else if(leftEdge < 0.0f)
            bird->move({ 0.0f - leftEdge, 0.0f });

        bird->HitGround();

        bird->TakeDamage(100.0f * deltaTime);
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
            {
                y = randomY;
                pipe->SetIsScored(false);
            }

            Pipe::IncreaseSpeed(10.0f);

            pipe->setPosition({ 1800.0f + pipe->getGlobalBounds().size.x / 2.0f, y });
        }
    }
}

void FlappyBird::CheckObjectBounds(float deltaTime)
{
    for(const auto& i : pipes)
    {
        auto intersection = bird->getGlobalBounds().findIntersection(i->getGlobalBounds());

        if(intersection.has_value())
        {
            if(intersection.value().size.x < intersection.value().size.y)
            {
                bird->ApplyForce({ 0.0f, 0.0f });
                bird->move({ -intersection.value().size.x, 0.0f });
            }
            else
            {
                bird->ApplyForce({ 0.0f, 0.01f * (i->getPosition().y > bird->getPosition().y ? -1.0f : 1.0f) });
                bird->move({ 0.0f, intersection.value().size.y * (i->getPosition().y > bird->getPosition().y ? -1.0f : 1.0f) });
            }

            bird->TakeDamage(100.0f * deltaTime);
        }
        else if(i->getPosition().x < bird->getPosition().x && !i->IsScored())
        {
            i->SetIsScored(true);
            score++;
        }
    }
}
