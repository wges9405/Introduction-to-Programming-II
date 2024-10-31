#include "GameWindow.h"

int main(int argc, char *argv[])
{
    GameWindow *Crazy_Arcade = new GameWindow();

    Crazy_Arcade->game_play();

    delete Crazy_Arcade;
    return 0;
}
