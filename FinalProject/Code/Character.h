#ifndef CHARACTER_H_INCLUDED
#define CHARACTER_H_INCLUDED

#include <stdio.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_primitives.h>
#include "Attack.h"
#include "Map.h"
#include "global.h"

#define Num_moveimg 4
#define max_waterball_power 15
#define max_waterball_quantity 7
#define max_character_speed 5.0


class Character
{
public:
    Character(int, int);
    virtual ~Character();

    void Draw(MAP*);
    void Load_Move();
    void move(int, MAP*);
    void buff(int);
    bool waterball_valid();
    void place_waterball();
    void be_attacked(MAP*);
    virtual int get_x() { return 0; };
    virtual int get_y() { return 0; };
public:
    char class_name[20];
    bool is_attacked = false;
    int type;
    bool die = false;
    bool stop = false;
    int push[3] = {0,0,5};

protected:
    int waterball_power = 0;
    int waterball_quantity = 0;
    float character_speed = 0.0;
    int direction = DOWN;
    std::vector<Attack*> attack_set;
    float pos_x, pos_y;
    const int boom_frequency = 25;
    int boom_counter = 0;

    ALLEGRO_BITMAP *moveimg[4];
    ALLEGRO_BITMAP *isAttacked = NULL;
    ALLEGRO_BITMAP *dead = NULL;
};

#endif
