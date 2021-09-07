#ifndef GLOBAL_H_INCLUDED
#define GLOBAL_H_INCLUDED

#include <allegro5/allegro_font.h>

#define window_width 800
#define window_height 600

#define field_width 675
#define field_height 585

#define Num_CharacterType 3
#define Num_ToolType 3
#define Num_MapType 3
#define Num_WallType 3
#define Num_ObstacleType 2

enum {LANBO = 0, KUNBO, ININ};
enum {WALL0 = 0 ,WALL1, WALL2, OBSTACLE0, OBSTACLE1, WATER, ROAD, BEATTACKED, TOOL, POWER, QUANTITY, SPEED, PUSH};
enum {LEFT=0, RIGHT, UP, DOWN};


#endif // GLOBAL_H_INCLUDED
