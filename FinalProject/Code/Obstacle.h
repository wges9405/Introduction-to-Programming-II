#ifndef OBSTACLE_H_INCLUDED
#define OBSTACLE_H_INCLUDED

#include <stdio.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_primitives.h>

class Obstacle
{
public:
    Obstacle(int,int);
    ~Obstacle();

    Draw();

private:
    int pos_x, pos_y;
};
#endif
