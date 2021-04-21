#include "game.hpp"
int main(int argc, char *args[])
{
    const int FPS_CAP = 60;
    const int SCREEN_TICKS_PER_FRAME = 1000 / FPS_CAP;
    Game game;
    game.init("Game title", 1280, 720, false);
    while (game.is_game_running())
    {
        int initial_ticks = SDL_GetTicks();
        game.handle_input();
        game.update();
        game.render();
        int frame_ticks = SDL_GetTicks() - initial_ticks;
        if (frame_ticks < SCREEN_TICKS_PER_FRAME)
        {
            SDL_Delay(SCREEN_TICKS_PER_FRAME - frame_ticks);
        }
    }

    game.clean();
    return 0;
}