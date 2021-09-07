#ifndef KUNBO_H_INCLUDED
#define KUNBO_H_INCLUDED

#include "Character.h"

class Kunbo : public Character {
public:
    Kunbo(int x = 0, int y = 0) : Character(x, y)
    {
        type = KUNBO;

        waterball_power = 1;
        waterball_quantity = 1;
        character_speed = 4.0;
        //img = al_load_bitmap("./Kunbo/.png");
        //waterball_img = al_load_bitmap("./WaterBall/WaterBall.png");

        strncpy(class_name, "Kunbo", 20);
        Load_Move();
    }

    int get_x() override { return pos_x; }
    int get_y() override { return pos_y; }

};

#endif // KUNBO_H_INCLUDED
