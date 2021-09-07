#ifndef ATTACK_H_INCLUDED
#define ATTACK_H_INCLUDED

#include <stdio.h>
#include "Map.h"
#include "global.h"
#include <allegro5/allegro.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_primitives.h>

class Attack {
public:
    Attack(int, int, int);
    ~Attack();

    void Draw(MAP*);
    void returnRoad(MAP*);

    bool explored = false;
    int explore_counter = 0;
    const int explore_frequency = 20;
    int get_x() { return pos_x; }
    int get_y() { return pos_y; }

protected:
    ALLEGRO_BITMAP *waterball_img;
    ALLEGRO_BITMAP *explore[5];

private:
    int pos_x, pos_y;
    int water_ball_power = 0;
    const int attack_frequency = 100;
    int attack_counter = 0;
    int flag[4];
};

#endif

