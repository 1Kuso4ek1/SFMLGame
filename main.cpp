#include <Game.hpp>

int main()
{
    Game game(sf::VideoMode({ 800, 600 }), "Game");

    game.Run();
}
