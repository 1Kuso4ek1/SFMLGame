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
    void SetupUI();

private:
    void PollEvent(const std::optional<sf::Event>& event) override;

    void Update(float deltaTime) override;

    void Render() override;

private:
    void ProcessInput();

private:
    void ProcessCollision(float deltaTime);

    void CheckScreenBounds(float deltaTime);
    void CheckObjectBounds(float deltaTime);

private:
    bool gameStarted = false;
    bool gameOver = false;

    sf::Clock flapTimer;

    int score = 0;

private: // Resources
    sf::Texture birdTexture;
    sf::Texture backgroundTexture;

    sf::Font openSans;

private: // Game objects
    BirdPtr bird;
    std::vector<PipePtr> pipes; 

    std::array<SpritePtr, 2> background;

private: // UI
    std::unique_ptr<sf::Text> healthText, scoreText, gameOverText;
    std::unique_ptr<sf::RectangleShape> healthBar;
};
