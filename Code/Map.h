#ifndef LEVEL_H_INCLUDED
#define LEVEL_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string>
#include <vector>
#include "global.h"
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_primitives.h>
/*
typedef struct Node {
    int h, g, f;
    bool roadPoint;
}Node;*/

class MAP {
public:
    MAP(const int);
    ~MAP();

    void setMap(const int);
    int getMap() {return map;}
    bool isRoad(int, int);
    bool isObstacle(int, int);
    bool isWall(int, int);
    int isTool(int, int);
    bool isWater(int, int);
    bool beAttacked(int, int);
    int get_player_index(int num) { return player_index[num]; }
    void change_value(int,int,int,int);
    void change_value_stright(int,int,int);
    bool can_be_push(int, int, int);
    bool push(int, int, int);

    void Draw();

private:
    int map = 0;
    int levelMap[13][15]; // 0 is wall , 1 is space , 2 is obstacle
    int player_index[2];
    float push_speed = 0.245;

    ALLEGRO_BITMAP *obstacle[10];
    ALLEGRO_BITMAP *wall[10];
    ALLEGRO_BITMAP *tool[3];
    ALLEGRO_BITMAP *floor;
};


#endif

