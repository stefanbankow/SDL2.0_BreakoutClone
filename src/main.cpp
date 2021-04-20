#include "game.hpp"
int main(int argc, char *args[])
{
    Game game;
    game.init("Game title", 1280, 720, false);
    while (game.is_game_running())
    {
        game.handle_input();
        game.update();
        game.render();
    }

    game.clean();
    return 0;
}