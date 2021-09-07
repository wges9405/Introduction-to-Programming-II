#ifndef LANBO_H_INCLUDED
#define LANBO_H_INCLUDED

#include "Character.h"

class Lanbo : public Character {
public:
    Lanbo(int x = 0, int y = 0) : Character(x, y)
    {
        type = LANBO;

        waterball_power = 2;
        waterball_quantity = 2;
        character_speed = 2.0;
        //img = al_load_bitmap("./Lanbo/3.png");
        //waterball_img = al_load_bitmap("./WaterBall/Waterball_1.png");

        strncpy(class_name, "Lanbo", 20);
        Load_Move();
    }

    int get_x() override { return pos_x; }
    int get_y() override { return pos_y; }

};

#endif // LANBO_H_INCLUDED
