#include <FlappyBird.hpp>

int main()
{
    FlappyBird game(sf::VideoMode({ 1280, 720 }), "FlappyBird");

    game.Run();
}
