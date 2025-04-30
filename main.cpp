#include <Game.hpp>

int main()
{
    Game game(sf::VideoMode({ 1280, 720 }), "Game");

    game.Run();
}
