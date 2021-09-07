#include "Attack.h"
#include "Map.h"
#include "global.h"

Attack::Attack(int x, int y, int power) {
    pos_x = x;
    pos_y = y;
    water_ball_power = power;
    waterball_img = al_load_bitmap("./WaterBall/Waterball_1.png");
    char buffer[50];
    for (int i = 0 ; i < 5 ; i++) {
        sprintf(buffer, "./WaterBall/explore_%d.png", i);
        explore[i] = al_load_bitmap(buffer);
    }
    for (int i = 0 ; i < 5 ; i++)
        flag[i] = water_ball_power;
}

Attack::~Attack(){
    al_destroy_bitmap(waterball_img);
    for (int i = 0 ; i < 5 ; i++) {
        al_destroy_bitmap(explore[i]);
    }
}
void
Attack::Draw(MAP *level){
    if (attack_counter++ != attack_frequency && !explored) {
        explored = false;
    }
    else {
        explored = true;
    }

    if (explored) {
        int x = pos_x , y = pos_y;
        al_draw_bitmap(explore[4], x*45, y*45, 0);
        level->change_value_stright(x, y, BEATTACKED);
        for (int i = 1 ; i <= flag[LEFT] ; i++) {

            if (level->isWall(x-i, y))
                flag[LEFT] = i-1;
            else if (level->isObstacle(x-i, y)) {
                flag[LEFT] = i-1;
                level->change_value_stright(x-i, y, TOOL);
            }
            else if ((level->isRoad(x-i, y) || level->isWater((x-i), y))) {
                al_draw_bitmap(explore[LEFT], (x-i)*45, y*45, 0);
                level->change_value_stright(x-i, y, BEATTACKED);
            }
        }
        for (int i = 1 ; i <= flag[RIGHT] ; i++) {
            if (level->isWall(x+i, y))
                flag[RIGHT] = i-1;
            else if (level->isObstacle(x+i, y)) {
                flag[RIGHT] = i-1;
                level->change_value_stright(x+i, y, TOOL);
            }
            else if ((level->isRoad(x+i, y) || level->isWater((x+i), y)) && x < 14) {
                al_draw_bitmap(explore[RIGHT], (x+i)*45, y*45, 0);
                level->change_value_stright(x+i, y, BEATTACKED);
            }
        }
        for (int i = 1 ; i <= flag[UP] ; i++) {
            if (level->isWall(x, y-i))
                flag[UP] = i-1;
            else if (level->isObstacle(x, y-i)) {
                flag[UP] = i-1;
                level->change_value_stright(x, y-i, TOOL);
            }
            else if ((level->isRoad(x, y-i) || level->isWater(x, y-i))) {
                al_draw_bitmap(explore[UP], x*45, (y-i)*45, 0);
                level->change_value_stright(x, y-i, BEATTACKED);
            }
        }
        for (int i = 1 ; i <= flag[DOWN] ; i++) {
            if (level->isWall(x, y+i))
                flag[DOWN] = i-1;
            else if (level->isObstacle(x, y+i)) {
                flag[DOWN] = i-1;
                level->change_value_stright(x, y+i, TOOL);
            }
            else if ((level->isRoad(x, y+i) || level->isWater(x, y+i))  && y < 12) {
                al_draw_bitmap(explore[DOWN], x*45, (y+i)*45, 0);
                level->change_value_stright(x, y+i, BEATTACKED);
            }

        }
    }
    else {
        al_draw_bitmap(waterball_img, pos_x*45, pos_y*45, 0);
        level->change_value_stright(pos_x, pos_y, WATER);
    }
}

void
Attack::returnRoad (MAP *level) {
    level->change_value_stright(pos_x, pos_y, ROAD);
    for (int i = 1 ; i <= water_ball_power ; i++) {
        if (level->beAttacked((pos_x-i), pos_y))
            level->change_value_stright(pos_x-i, pos_y, ROAD);
        if (level->beAttacked(pos_x+i, pos_y))
            level->change_value_stright(pos_x+i, pos_y, ROAD);
        if (level->beAttacked(pos_x, pos_y-i))
            level->change_value_stright(pos_x, pos_y-i, ROAD);
        if (level->beAttacked(pos_x, pos_y+i))
            level->change_value_stright(pos_x, pos_y+i, ROAD);
    }
}
