#pragma once
#include <Application.hpp>
#include <Bird.hpp>
#include <Pipe.hpp>

class FlappyBird : public Application
{
public:
    FlappyBird(const sf::VideoMode& mode, const std::string& name);
    ~FlappyBird() = default;

private:
    void SetupGame();

private:
    void PollEvent(const std::optional<sf::Event>& event) override;

    void Update(float deltaTime) override;

    void Render() override;

private:
    void ProcessInput();

private:
    void ProcessCollision();

    void CheckScreenBounds();
    void CheckObjectBounds();

private:
    bool gameStarted = false;
    bool gameOver = false;

    sf::Clock flapTimer;

private:
    sf::Texture birdTexture;
    sf::Texture pipeTexture;
    sf::Texture backgroundTexture;

    BirdPtr bird;
    std::vector<PipePtr> pipes; 
};
