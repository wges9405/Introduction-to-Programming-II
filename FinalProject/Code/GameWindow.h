#ifndef MAINWINDOW_H_INCLUDED
#define MAINWINDOW_H_INCLUDED

#include <allegro5/allegro.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <vector>
#include <list>
#include <map>
#include <time.h>
#include "global.h"
#include "Menu.h"
#include "Map.h"
#include "Tool.h"
#include "Character.h"
#include "Lanbo.h"
#include "Kunbo.h"
#include "Inin.h"
#include "Attack.h"
#include "WaterBall.h"
#include "Slider.h"
#include "Obstacle.h"

using namespace std;

const float FPS = 60;

class GameWindow
{
public:
    GameWindow();

    void game_init();
    void game_reset();
    void game_play();

    bool game_sign_in();
    bool New_User();
    bool game_start_scene();
    bool game_select_character();
    bool game_select_map();
    bool game_setting();

    void game_begin();
    Character* create_char(int, int);
    bool game_run();
    void game_update();
    void draw_running_map();
    int process_event();
    bool game_endding();
    void game_destroy();

private:
    ALLEGRO_FONT *title = NULL;
    ALLEGRO_FONT *title2 = NULL;
    ALLEGRO_FONT *title3 = NULL;
    ALLEGRO_FONT *endding = NULL;
    ALLEGRO_FONT *time = NULL;
    ALLEGRO_FONT *sign = NULL;
    ALLEGRO_FONT *create = NULL;

    ALLEGRO_BITMAP *icon = NULL;
    ALLEGRO_BITMAP *character[Num_CharacterType];
    ALLEGRO_BITMAP *Map[Num_MapType];
    ALLEGRO_BITMAP *background1 = NULL;
    ALLEGRO_BITMAP *background2 = NULL;
    ALLEGRO_BITMAP *background3 = NULL;
    ALLEGRO_BITMAP *sign_in = NULL;
    ALLEGRO_BITMAP *start = NULL;
    ALLEGRO_BITMAP *confirm = NULL;

    ALLEGRO_DISPLAY* display = NULL;

    ALLEGRO_EVENT_QUEUE *event_queue = NULL;
    ALLEGRO_EVENT event;
    ALLEGRO_TIMER *timer = NULL;
    ALLEGRO_TIMER *playing_timer = NULL;

    ALLEGRO_SAMPLE *sample = NULL;
    ALLEGRO_SAMPLE_INSTANCE *homesound = NULL;
    ALLEGRO_SAMPLE_INSTANCE *mapsound = NULL;

    MAP *level = NULL;
    char ALLaccount[5][20];
    char ALLpassword[5][20];
    char account[20] = {'\0'}, password[20] = {'\0'};
    char change_line[2] = {'\r','\n'};

    Character *Player1, *Player2;
    bool move1[4] = {false,false,false,false}, move2[4] = {false,false,false,false};

    int mouse_x, mouse_y;
    int Time = 0;
    bool ready1 = false, ready2 = false;
    int player1 = 0, player2 = 0;
    bool redraw = false;
    int selectMap = 0;
    bool mute = false;
    bool pause = false;
    bool playing = false;
    int P1, P2;
};



#endif // MAINWINDOW_H_INCLUDED
