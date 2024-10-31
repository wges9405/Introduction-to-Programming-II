#ifndef WATER_BALL_H_INCLUDED
#define WATER_BALL_H_INCLUDED

#include <stdio.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_primitives.h>

class WaterBall
{
public:
    WaterBall(int, int);
    ~WaterBall();

    void Draw();

    bool exploredTime();

protected:
    ALLEGRO_BITMAP *attack_img;
    ALLEGRO_SAMPLE *sample;
    ALLEGRO_SAMPLE_INSTANCE *arrow = NULL;

private:
    int pos_x, pos_y;
};

#endif
