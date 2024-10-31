#ifndef MENU_H_INCLUDED
#define MENU_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_primitives.h>
#include <vector>
#include "global.h"

class Menu
{
public:
    Menu();
    ~Menu();

    void Reset();
    void Draw();
    void Time_count();

private:
    std::vector<ALLEGRO_BITMAP*> menu_character;
    ALLEGRO_FONT *menuFont;
};

#endif // MENU_H_INCLUDED

