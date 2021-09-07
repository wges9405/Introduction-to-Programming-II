#ifndef ININ_H_INCLUDED
#define ININ_H_INCLUDED

#include "Character.h"

class Inin : public Character {
public:
    Inin(int x = 0, int y = 0) : Character(x, y)
    {
        type = ININ;

        waterball_power = 3;
        waterball_quantity = 1;
        character_speed = 2.0;
        //img = al_load_bitmap("./Inin/3.png");
        //waterball_img = al_load_bitmap("./WaterBall/WaterBall.png");

        strncpy(class_name, "Inin", 20);
        Load_Move();
    }

    int get_x() override { return pos_x; }
    int get_y() override { return pos_y; }

};

#endif // ININ_H_INCLUDED
