#include "Map.h"
#include "GameWindow.h"
#include <ctype.h>
#include <stdlib.h>
MAP::MAP(const int num) {
    char buffer[50];
    for (int i = 0 ; i < Num_WallType ; i++) {
        sprintf(buffer, "./map%d/Wall_%d.png", num, i);
        wall[i] = al_load_bitmap(buffer);
    }
    for (int i = 0 ; i < Num_ObstacleType ; i++) {
        sprintf(buffer, "./map%d/Obstacle_%d.png", num, i);
        obstacle[i] = al_load_bitmap(buffer);
    }
    sprintf(buffer, "./map%d/floor.png", num);
    floor = al_load_bitmap(buffer);
    tool[0] = al_load_bitmap("./Tool/POWER.png");
    tool[1] = al_load_bitmap("./Tool/QUANTITY.png");
    tool[2] = al_load_bitmap("./Tool/SPEED.png");

    setMap(num);
}

MAP::~MAP() {
    for (int i = 0 ; i < Num_WallType ; i++)
        al_destroy_bitmap(wall[i]);
    for (int i = 0 ; i < Num_ObstacleType ; i++)
        al_destroy_bitmap(obstacle[i]);
    for (int i = 0 ; i < Num_ToolType ; i++)
        al_destroy_bitmap(tool[i]);
    al_destroy_bitmap(floor);
}

void
MAP::setMap(const int num) {
    char buffer[50];
    int player = 0;
    FILE *file;

    sprintf(buffer, "./Map/Map%d.txt", num);
    file = fopen(buffer, "r");

    this->map = num;
    for (int y = 0 ; y < 13; y++)
        for (int x = 0 ; x < 15 ; x++)
            this->levelMap[y][x] = 0;
    while(fscanf(file, "%s", buffer) != EOF) {
        if (strcmp(buffer, "road")==0) break;
        int index = atoi(buffer);
        this->player_index[player++] = index;
    }
    while(fscanf(file, "%s", buffer) != EOF) {
        if (strcmp(buffer, "obstacle_0")==0) break;
        int index = atoi(buffer);
        this->levelMap[index/15][index%15] = ROAD;
    }
    while(fscanf(file, "%s", buffer) != EOF) {
        if (strcmp(buffer, "obstacle_1")==0) break;
        int index = atoi(buffer);
        this->levelMap[index/15][index%15] = OBSTACLE0;
    }
    while(fscanf(file, "%s", buffer) != EOF) {
        if (strcmp(buffer, "wall_0")==0) break;
        int index = atoi(buffer);
        this->levelMap[index/15][index%15] = OBSTACLE1;
    }while(fscanf(file, "%s", buffer) != EOF) {
        if (strcmp(buffer, "wall_1")==0) break;
        int index = atoi(buffer);
        this->levelMap[index/15][index%15] = WALL0;
    }
    while(fscanf(file, "%s", buffer) != EOF) {
        if (strcmp(buffer, "wall_2")==0) break;
        int index = atoi(buffer);
        this->levelMap[index/15][index%15] = WALL1;
    }
    while(fscanf(file, "%s", buffer) != EOF) {
        int index = atoi(buffer);
        this->levelMap[index/15][index%15] = WALL2;
    }
    /*for (int y = 0 ; y < 13; y++) {
        for (int x = 0 ; x < 15 ; x++)
            printf("%d", this->levelMap[y][x]);
        printf("\n");
    }*/
    fclose(file);
}

bool
MAP::isWall(int x, int y) {
    if (x<0 || x>15 || y<0 || y>13) return false;
    if (levelMap[y][x] >= WALL0 && levelMap[y][x] <= WALL2) return true;
    else return false;
}

bool
MAP::isObstacle(int x, int y) {
    if (x<0 || x>15 || y<0 || y>13) return false;
    if (levelMap[y][x] >= OBSTACLE0 && levelMap[y][x] <= OBSTACLE1) return true;
    else return false;
}

bool
MAP::isWater(int x, int y) {
    if (levelMap[y][x] == WATER) return true;
    else return false;
}

bool
MAP::isRoad(int x, int y) {
    if (x<0 || x>15 || y<0 || y>13) return false;
    if (levelMap[y][x] >= ROAD && levelMap[y][x] <= SPEED) return true;
    else return false;
}

bool
MAP::beAttacked(int x, int y) {
    if (levelMap[y][x] == BEATTACKED) return true;
    else return false;
}

int
MAP::isTool(int x, int y) {
    if (levelMap[y][x] >= TOOL) return levelMap[y][x];
    else return 0;
}

void
MAP::Draw() {
    for (int y = 0 ; y < 13 ; y++)
        for (int x = 0 ; x < 15 ; x++) {
            al_draw_bitmap(floor, x*45, y*45, 0);
            if (levelMap[y][x] == WALL0) al_draw_bitmap(wall[0], x*45, y*45, 0);
            else if (levelMap[y][x] == WALL1) al_draw_bitmap(wall[1], x*45, y*45, 0);
            else if (levelMap[y][x] == WALL2) al_draw_bitmap(wall[2], x*45, y*45, 0);
            else if (levelMap[y][x] == OBSTACLE0) al_draw_bitmap(obstacle[0], x*45, y*45, 0);
            else if (levelMap[y][x] == OBSTACLE1) al_draw_bitmap(obstacle[1], x*45, y*45, 0);

            if (levelMap[y][x] == TOOL) {
                int order = rand()%6;
                if (order <= 2) {
                    al_draw_bitmap(tool[order], x*45, y*45, 0);
                    levelMap[y][x] = order+9;
                }
                else levelMap[y][x] = ROAD;
            }
            else if (levelMap[y][x] == POWER) {
                al_draw_bitmap(tool[0], x*45, y*45, 0);
            }
            else if (levelMap[y][x] == QUANTITY) {
                al_draw_bitmap(tool[1], x*45, y*45, 0);
            }
            else if (levelMap[y][x] == SPEED) {
                al_draw_bitmap(tool[2], x*45, y*45, 0);
            }
        }
}

void
MAP::change_value(int x, int y, int power, int val) {
    this->levelMap[y][x] = val;
    for (int i = 1 ; i <= power ; i++) {
        this->levelMap[y][x-i] = val;
        this->levelMap[y][x+i] = val;
        this->levelMap[y-i][x] = val;
        this->levelMap[y+i][x] = val;
    }
}

void
MAP::change_value_stright(int x, int y, int val) {
     this->levelMap[y][x] = val;
}

bool
MAP::can_be_push(int x, int y, int dir) {
    switch (dir) {
        case LEFT:
            if ((levelMap[y][x-1] == OBSTACLE0) && (levelMap[y][x-2] == ROAD)) {
                levelMap[y][x-1] = PUSH;
                levelMap[y][x-2] = PUSH;
                return true;
            }
            break;
        case RIGHT:
            if ((levelMap[y][x+1] == OBSTACLE0) && (levelMap[y][x+2] == ROAD)) {
                levelMap[y][x+1] = PUSH;
                levelMap[y][x+2] = PUSH;
                return true;
            }
            break;
        case UP:
            if ((levelMap[y-1][x] == OBSTACLE0) && (levelMap[y-2][x] == ROAD)) {
                levelMap[y-1][x] = PUSH;
                levelMap[y-2][x] = PUSH;
                return true;
            }
            break;
        case DOWN:
            if ((levelMap[y+1][x] == OBSTACLE0) && (levelMap[y+2][x] == ROAD)) {
                levelMap[y+1][x] = PUSH;
                levelMap[y+2][x] = PUSH;
                return true;
            }
            break;
    }
    return false;
}

bool
MAP::push(int x, int y, int dir) {
    switch (dir) {
        case LEFT:
            for (int i = 0 ; i <= 200 ; i++) al_draw_bitmap(obstacle[0], x*45-i*push_speed, y*45, 0);
            levelMap[y][x] = ROAD;
            levelMap[y][x-1] = OBSTACLE0;
            break;
        case RIGHT:
            for (int i = 0 ; i <= 200 ; i++) al_draw_bitmap(obstacle[0], x*45+i*push_speed, y*45, 0);
            levelMap[y][x] = ROAD;
            levelMap[y][x+1] = OBSTACLE0;
            break;
        case UP:
            for (int i = 0 ; i <= 200 ; i++) al_draw_bitmap(obstacle[0], x*45, y*45-i*push_speed, 0);
            levelMap[y][x] = ROAD;
            levelMap[y-1][x] = OBSTACLE0;
            break;
        case DOWN:
            for (int i = 0 ; i <= 200 ; i++) al_draw_bitmap(obstacle[0], x*45, y*45+i*push_speed, 0);
            levelMap[y][x] = ROAD;
            levelMap[y+1][x] = OBSTACLE0;
            break;
    }
    return true;
}
