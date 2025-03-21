#include "GameWindow.h"
#include "global.h"
#include <iostream>
#include <fstream>
#include <string.h>

using namespace std;

GameWindow::GameWindow()
{
    if (!al_init());

    printf("Game Initializing...\n");

    display = al_create_display(window_width, window_height);
    event_queue = al_create_event_queue();

    timer = al_create_timer(1.0 / FPS);
    playing_timer = al_create_timer(1.0);

    al_init_primitives_addon();
    al_init_font_addon(); // initialize the font addon
    al_init_ttf_addon(); // initialize the ttf (True Type Font) addon
    al_init_image_addon(); // initialize the image addon
    al_init_acodec_addon(); // initialize acodec addon

    al_install_keyboard(); // install keyboard event
    al_install_mouse();    // install mouse event
    al_install_audio();    // install audio event

    al_register_event_source(event_queue, al_get_display_event_source(display));
    al_register_event_source(event_queue, al_get_keyboard_event_source());
    al_register_event_source(event_queue, al_get_mouse_event_source());

    al_register_event_source(event_queue, al_get_timer_event_source(timer));
    al_register_event_source(event_queue, al_get_timer_event_source(playing_timer));

    sign_in = al_load_bitmap("./picture/sign_in.jpg");
    background1 = al_load_bitmap("./picture/background1.png");
    background2 = al_load_bitmap("./picture/background2.png");
    background3 = al_load_bitmap("./picture/background3.png");
    start = al_load_bitmap("./picture/Start.png");
    confirm = al_load_bitmap("./picture/confirm.png");
    char buffer[50];
    for(int i = 0; i < Num_CharacterType; i++) {
        sprintf(buffer, "./picture/character%d.png", i);
        character[i] = al_load_bitmap(buffer);
    }
    for(int i = 0; i < Num_MapType; i++) {
        sprintf(buffer, "./Map/Map_%d.png", i);
        Map[i] = al_load_bitmap(buffer);
    }

    game_init();
}

void
GameWindow::game_init()
{
    icon = al_load_bitmap("./picture/icon.png");
    al_set_display_icon(display, icon);
    al_reserve_samples(5);

    title = al_load_ttf_font("./font/SHREK.ttf",70,0);
    title2 = al_load_ttf_font("./font/Caviar_Dreams_Bold.ttf",50,0);
    title3 = al_load_ttf_font("./font/Caviar_Dreams_Bold.ttf",30,0);
    endding = al_load_ttf_font("./font/endding.ttf",50,0);
    time = al_load_ttf_font("./font/time.ttf", 30,0);
    sign = al_load_ttf_font("./font/Bebas.ttf", 15,0);
    create = al_load_ttf_font("./font/time.ttf", 15,0);

    sample = al_load_sample("back.wav");
    homesound = al_create_sample_instance(sample);
    al_set_sample_instance_playmode(homesound, ALLEGRO_PLAYMODE_ONCE);
    al_attach_sample_instance_to_mixer(homesound, al_get_default_mixer());

    FILE *file;
    char _account[20];
    char _password[20];
    file = fopen("ALLaccount.txt", "r");
    int i = 0;
    while (fscanf(file, "%s", _account) != EOF && fscanf(file, "%s", _password) != EOF) {
        strcpy(ALLaccount[i], _account);
        strcpy(ALLpassword[i++], _password);
    }
    fclose(file);
}

void
GameWindow::game_reset()
{
    al_stop_timer(playing_timer);
    delete Player1;
    delete Player2;
    delete level;
    selectMap = 0;
    ready1 = false;
    ready2 = false;
    player1 = 0;
    player2 = 0;

    bool Go = false;
    Go = false;
    while (!Go)
        Go = game_select_character();
    Go = false;
    while (!Go)
        Go = game_select_map();

    game_begin();

    Go = false;
    while (!Go)
        Go = game_run();
    al_stop_sample_instance(mapsound);
    al_play_sample_instance(homesound);
    Go = false;
    while (!Go)
        Go = game_endding();

    game_reset();
}

void
GameWindow::game_play()
{
    al_start_timer(timer);
    al_play_sample_instance(homesound);
    bool Go = false;
    while (!Go)
        Go = game_sign_in();
    Go = false;
    while (!Go)
        Go = game_select_character();
    Go = false;
    while (!Go)
        Go = game_select_map();

    game_begin();

    Go = false;
    while (!Go)
        Go = game_run();
    al_stop_sample_instance(mapsound);
    al_play_sample_instance(homesound);
    Go = false;
    while (!Go)
        Go = game_endding();

    game_reset();

}

bool
GameWindow::game_sign_in()
{
    static int order = 0;
    static bool flag = false;
    bool redraw = false;
    al_wait_for_event(event_queue, &event);

    if (event.type == ALLEGRO_EVENT_TIMER) {
        redraw = true;
    }
    else if(event.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
        game_destroy();
        exit(0);
    }
    else if(event.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN) {
        if(event.mouse.button==1){
            if (mouse_x<=343 && mouse_x>=242 && mouse_y<=590 && mouse_y>=560) {
                flag = false;
                order = 0;
                for (int i = 0 ; i < 20 ; i++) {
                    account[i] = {'\0'};
                    password[i] = {'\0'};
                }
                bool Go = false;
                while (!Go)
                    Go = New_User();
            }
            if(mouse_x<=453 && mouse_x>=352 && mouse_y<=590 && mouse_y>=560 && flag) {
                int i;
                for (i = 0 ; i < 5 ; i++) if (strcmp(account, ALLaccount[i]) == 0 ) break;
                if (i == 5) {
                    printf("Account didn't exist\n");
                    for (int i = 0 ; i < 20 ; i++) {
                        account[i] = {'\0'};
                        password[i] = {'\0'};
                    }
                }
                else {
                    if (strcmp(password, ALLpassword[i]) == 0) return true;
                    else {
                        printf("Wrong password\n");
                        for (int i = 0 ; i < 20 ; i++) {
                            account[i] = {'\0'};
                            password[i] = {'\0'};
                        }
                    }
                }
            }
            if (mouse_x<=561 && mouse_x>=460 && mouse_y<=590 && mouse_y>=560) {
                game_destroy();
                exit(0);
            }
        }
    }
    else if(event.type == ALLEGRO_EVENT_KEY_DOWN) {
         switch (event.keyboard.keycode) {
            case ALLEGRO_KEY_ESCAPE:
                game_destroy();
                exit(0);
                break;
            case ALLEGRO_KEY_ENTER:
                if (flag) {
                    int i;
                    for (i = 0 ; i < 5 ; i++) if (strcmp(account, ALLaccount[i]) == 0 ) break;
                    if (i == 5) {
                        printf("Account didn't exist\n");
                        for (int i = 0 ; i < 20 ; i++) {
                            account[i] = {'\0'};
                            password[i] = {'\0'};
                        }
                    }
                    else {
                        if (strcmp(password, ALLpassword[i]) == 0) return true;
                        else {
                            printf("Wrong password\n");
                            for (int i = 0 ; i < 20 ; i++) {
                                account[i] = {'\0'};
                                password[i] = {'\0'};
                            }
                        }
                    }
                }
                order = 0;
                flag = !flag;
                break;
            case ALLEGRO_KEY_BACKSPACE:
                if (order == 0) order = 0;
                else order--;
                if (!flag) account[order] = '\0';
                else password[order] = '\0';
                break;
            case ALLEGRO_KEY_A:
                if (order < 20) {
                    if (!flag) account[order++] = 'a';
                    else password[order++] = 'a';
                }
                break;
            case ALLEGRO_KEY_B:
                if (order < 20) {
                    if (!flag) account[order++] = 'b';
                    else password[order++] = 'b';
                }
                break;
            case ALLEGRO_KEY_C:
                if (order < 20) {
                    if (!flag) account[order++] = 'c';
                    else password[order++] = 'c';
                }
                break;
            case ALLEGRO_KEY_D:
                if (order < 20) {
                    if (!flag) account[order++] = 'd';
                    else password[order++] = 'd';
                }
                break;
            case ALLEGRO_KEY_E:
                if (order < 20) {
                    if (!flag) account[order++] = 'e';
                    else password[order++] = 'e';
                }
                break;
            case ALLEGRO_KEY_F:
                if (order < 20) {
                    if (!flag) account[order++] = 'f';
                    else password[order++] = 'f';
                }
                break;
            case ALLEGRO_KEY_G:
                if (order < 20) {
                    if (!flag) account[order++] = 'g';
                    else password[order++] = 'g';
                }
                break;
            case ALLEGRO_KEY_H:
                if (order < 20) {
                    if (!flag) account[order++] = 'h';
                    else password[order++] = 'h';
                }
                break;
            case ALLEGRO_KEY_I:
                if (order < 20) {
                    if (!flag) account[order++] = 'i';
                    else password[order++] = 'i';
                }
                break;
            case ALLEGRO_KEY_J:
                if (order < 20) {
                    if (!flag) account[order++] = 'j';
                    else password[order++] = 'j';
                }
                break;
            case ALLEGRO_KEY_K:
                if (order < 20) {
                    if (!flag) account[order++] = 'k';
                    else password[order++] = 'k';
                }
                break;
            case ALLEGRO_KEY_L:
                if (order < 20) {
                    if (!flag) account[order++] = 'l';
                    else password[order++] = 'l';
                }
                break;
            case ALLEGRO_KEY_M:
                if (order < 20) {
                    if (!flag) account[order++] = 'm';
                    else password[order++] = 'm';
                }
                break;
            case ALLEGRO_KEY_N:
                if (order < 20) {
                    if (!flag) account[order++] = 'n';
                    else password[order++] = 'n';
                }
                break;
            case ALLEGRO_KEY_O:
                if (order < 20) {
                    if (!flag) account[order++] = 'o';
                    else password[order++] = 'o';
                }
                break;
            case ALLEGRO_KEY_P:
                if (order < 20) {
                    if (!flag) account[order++] = 'p';
                    else password[order++] = 'p';
                }
                break;
            case ALLEGRO_KEY_Q:
                if (order < 20) {
                    if (!flag) account[order++] = 'q';
                    else password[order++] = 'q';
                }
                break;
            case ALLEGRO_KEY_R:
                if (order < 20) {
                    if (!flag) account[order++] = 'r';
                    else password[order++] = 'r';
                }
                break;
            case ALLEGRO_KEY_S:
                if (order < 20) {
                    if (!flag) account[order++] = 's';
                    else password[order++] = 's';
                }
                break;
            case ALLEGRO_KEY_T:
                if (order < 20) {
                    if (!flag) account[order++] = 't';
                    else password[order++] = 't';
                }
                break;
            case ALLEGRO_KEY_U:
                if (order < 20) {
                    if (!flag) account[order++] = 'u';
                    else password[order++] = 'u';
                }
                break;
            case ALLEGRO_KEY_V:
                if (order < 20) {
                    if (!flag) account[order++] = 'v';
                    else password[order++] = 'v';
                }
                break;
            case ALLEGRO_KEY_W:
                if (order < 20) {
                    if (!flag) account[order++] = 'w';
                    else password[order++] = 'w';
                }
                break;
            case ALLEGRO_KEY_X:
                if (order < 20) {
                    if (!flag) account[order++] = 'x';
                    else password[order++] = 'y';
                }
                break;
            case ALLEGRO_KEY_Y:
                if (order < 20) {
                    if (!flag) account[order++] = 'y';
                    else password[order++] = 'x';
                }
                break;
            case ALLEGRO_KEY_Z:
                if (order < 20) {
                    if (!flag) account[order++] = 'z';
                    else password[order++] = 'z';
                }
                break;
            case ALLEGRO_KEY_0:
                if (order < 20) {
                    if (!flag) account[order++] = '0';
                    else password[order++] = '0';
                }
                break;
            case ALLEGRO_KEY_1:
                if (order < 20) {
                    if (!flag) account[order++] = '1';
                    else password[order++] = '1';
                }
                break;
            case ALLEGRO_KEY_2:
                if (order < 20) {
                    if (!flag) account[order++] = '2';
                    else password[order++] = '2';
                }
                break;
            case ALLEGRO_KEY_3:
                if (order < 20) {
                    if (!flag) account[order++] = '3';
                    else password[order++] = '3';
                }
                break;
            case ALLEGRO_KEY_4:
                if (order < 20) {
                    if (!flag) account[order++] = '4';
                    else password[order++] = '4';
                }
                break;
            case ALLEGRO_KEY_5:
                if (order < 20) {
                    if (!flag) account[order++] = '5';
                    else password[order++] = '5';
                }
                break;
            case ALLEGRO_KEY_6:
                if (order < 20) {
                    if (!flag) account[order++] = '6';
                    else password[order++] = '6';
                }
                break;
            case ALLEGRO_KEY_7:
                if (order < 20) {
                    if (!flag) account[order++] = '7';
                    else password[order++] = '7';
                }
                break;
            case ALLEGRO_KEY_8:
                if (order < 20) {
                    if (!flag) account[order++] = '8';
                    else password[order++] = '8';
                }
                break;
            case ALLEGRO_KEY_9:
                if (order < 20) {
                    if (!flag) account[order++] = '9';
                    else password[order++] = '9';
                }
                break;
         }
    }
    else if(event.type == ALLEGRO_EVENT_MOUSE_AXES) {
        mouse_x = event.mouse.x;
        mouse_y = event.mouse.y;
    }

    if (redraw) {
        al_clear_to_color(al_map_rgb(255, 255, 255));
        al_draw_bitmap(sign_in, 0, 0, 0);
        if (!flag) {
            al_draw_textf(sign, al_map_rgb(0,0,0), 403, 444, ALLEGRO_ALIGN_LEFT, "%s", account);
            al_draw_line(404+(order)*8, 462, 412+(order)*8, 462, al_map_rgb(255, 125, 125), 2);
            al_draw_rounded_rectangle(352,560,453,590,1,1,al_map_rgb(0,0,255),3);
        }
        else {
            al_draw_textf(sign, al_map_rgb(0,0,0), 403, 444, ALLEGRO_ALIGN_LEFT, "%s", account);
            al_draw_textf(sign, al_map_rgb(0,0,0), 403, 469, ALLEGRO_ALIGN_LEFT, "%s", password);
            al_draw_line(404+(order)*8, 487, 412+(order)*8, 487, al_map_rgb(255, 125, 125), 2);
            al_draw_bitmap(confirm, 352,560, 0);
            if(mouse_x<=453 && mouse_x>=352 && mouse_y<=590 && mouse_y>=560) {
                al_draw_rounded_rectangle(352,560,453,590,1,1,al_map_rgb(150,150,255),3);
            }
            else {
                al_draw_rounded_rectangle(352,560,453,590,1,1,al_map_rgb(0,0,255),3);
            }
        }
        if(mouse_x<=343 && mouse_x>=242 && mouse_y<=590 && mouse_y>=560) {
            al_draw_rounded_rectangle(242,560,343,590,1,1,al_map_rgb(150,150,255),3);
        }
        else {
            al_draw_rounded_rectangle(242,560,343,590,1,1,al_map_rgb(0,0,255),3);
        }
        if(mouse_x<=561 && mouse_x>=460 && mouse_y<=590 && mouse_y>=560) {
            al_draw_rounded_rectangle(460,560,561,590,1,1,al_map_rgb(150,150,255),3);
        }
        else {
            al_draw_rounded_rectangle(460,560,561,590,1,1,al_map_rgb(0,0,255),3);
        }
        al_flip_display();
    };
    return false;
}

bool
GameWindow::game_start_scene()
{
    al_wait_for_event(event_queue, &event);

    al_clear_to_color(al_map_rgb(255, 142, 71));
    al_draw_bitmap(start,0,0,0);
    al_draw_text(title,al_map_rgb(255,255,0),400,50,ALLEGRO_ALIGN_CENTER,"BOOM GAME");
    al_draw_text(title2,al_map_rgb(255,255,255),400,530,ALLEGRO_ALIGN_CENTER,"Press Enter to Start");
    al_flip_display();
    if(event.type == ALLEGRO_EVENT_KEY_DOWN){
        if(event.keyboard.keycode == ALLEGRO_KEY_ENTER){
            return true;
        }
    }
    return false;
}

bool
GameWindow::New_User()
{
    static int order = 0;
    static int flag = 0;
    static int Aorder = 0, Porder = 0;
    static char Naccount[20] = {'\0'}, Npassword[20] = {'\0'}, Cpassword[20] = {'\0'};
    bool redraw = false, used = false;
    al_wait_for_event(event_queue, &event);

    if (event.type == ALLEGRO_EVENT_TIMER) {
        redraw = true;
    }
    else if(event.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
        game_destroy();
        exit(0);
    }
    else if(event.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN) {
        if(event.mouse.button==1){
            if(mouse_x<= 800 && mouse_x>=650 && mouse_y<=595 && mouse_y>=525){
                order = 0;
                flag = 0;
                for (int i = 0 ; i < 20 ; i++) {
                    Naccount[i] = {'\0'};
                    Npassword[i] = {'\0'};
                    Cpassword[i] = {'\0'};
                }
                return true;
            }
            else if(mouse_x<=340 && mouse_x>=260 && mouse_y<=295 && mouse_y>=270){
                int i;
                for (i = 0 ; i < 5 ; i++) {
                    if (strcmp(ALLaccount[i], Naccount) == 0) {
                        used = true;
                        printf("New account is already used.\n");
                        for (int i = 0 ; i < 20 ; i++) {
                            Naccount[i] = {'\0'};
                            Npassword[i] = {'\0'};
                            Cpassword[i] = {'\0'};
                        }
                        break;
                    }
                }
                if (flag == 3 && !used) {
                    flag = 0;
                    order = 0;
                    if (strcmp(Npassword, Cpassword) == 0) {
                        FILE *file;
                        file = fopen("ALLaccount.txt", "a+");
                        fputs(change_line, file);
                        fputs(Naccount, file);
                        fputs(change_line, file);
                        fputs(Npassword,file);
                        fclose(file);

                        printf("Creating new account Success.\n");

                        char _account[20];
                        char _password[20];
                        file = fopen("ALLaccount.txt", "r");
                        int i = 0;
                        while (fscanf(file, "%s", _account) != EOF && fscanf(file, "%s", _password) != EOF) {
                            strcpy(ALLaccount[i], _account);
                            strcpy(ALLpassword[i++], _password);
                        }
                        fclose(file);
                    }
                    else {
                        printf("Confirm password is different from New password.\n");
                        printf("Please type again.\n");
                    }
                    for (int i = 0 ; i < 20 ; i++) {
                        Naccount[i] = {'\0'};
                        Npassword[i] = {'\0'};
                        Cpassword[i] = {'\0'};
                    }
                }
                used = false;
            }
            else if(mouse_x<=440 && mouse_x>=360 && mouse_y<=295 && mouse_y>=270){
                flag = 0;
                order = 0;
                for (int i = 0 ; i < 20 ; i++) {
                    Naccount[i] = {'\0'};
                    Npassword[i] = {'\0'};
                    Cpassword[i] = {'\0'};
                }
            }
        }
    }
    else if(event.type == ALLEGRO_EVENT_KEY_DOWN) {
         switch (event.keyboard.keycode) {
             case ALLEGRO_KEY_ESCAPE:
                game_destroy();
                exit(0);
                break;
            case ALLEGRO_KEY_ENTER:
                if (flag == 0) {
                    Aorder = order;
                    flag = 1;
                }
                else if (flag == 1) {
                    Porder = order;
                    flag = 2;
                }
                else if (flag == 2) flag = 3;
                order = 0;
                break;
            case ALLEGRO_KEY_BACKSPACE:
                if (order == 0) order = 0;
                else {
                    if (flag == 0) Naccount[--order] = '\0';
                    else if (flag == 1) Npassword[--order] = '\0';
                    else if (flag == 2) Cpassword[--order] = '\0';
                }
                break;
            case ALLEGRO_KEY_A:
                if (order < 20) {
                    if (flag == 0) Naccount[order++] = 'a';
                    else if (flag == 1) Npassword[order++] = 'a';
                    else if (flag == 2) Cpassword[order++] = 'a';
                }
                break;
            case ALLEGRO_KEY_B:
                if (order < 20) {
                    if (flag == 0) Naccount[order++] = 'b';
                    else if (flag == 1) Npassword[order++] = 'b';
                    else if (flag == 2) Cpassword[order++] = 'b';
                }
                break;
            case ALLEGRO_KEY_C:
                if (order < 20) {
                    if (flag == 0) Naccount[order++] = 'c';
                    else if (flag == 1) Npassword[order++] = 'c';
                    else if (flag == 2) Cpassword[order++] = 'c';
                }
                break;
            case ALLEGRO_KEY_D:
                if (order < 20) {
                    if (flag == 0) Naccount[order++] = 'd';
                    else if (flag == 1) Npassword[order++] = 'd';
                    else if (flag == 2) Cpassword[order++] = 'd';
                }
                break;
            case ALLEGRO_KEY_E:
                if (order < 20) {
                    if (flag == 0) Naccount[order++] = 'e';
                    else if (flag == 1) Npassword[order++] = 'e';
                    else if (flag == 2) Cpassword[order++] = 'e';;
                }
                break;
            case ALLEGRO_KEY_F:
                if (order < 20) {
                    if (flag == 0) Naccount[order++] = 'f';
                    else if (flag == 1) Npassword[order++] = 'f';
                    else if (flag == 2) Cpassword[order++] = 'f';
                }
                break;
            case ALLEGRO_KEY_G:
                if (order < 20) {
                    if (flag == 0) Naccount[order++] = 'g';
                    else if (flag == 1) Npassword[order++] = 'g';
                    else if (flag == 2) Cpassword[order++] = 'g';
                }
                break;
            case ALLEGRO_KEY_H:
                if (order < 20) {
                    if (flag == 0) Naccount[order++] = 'h';
                    else if (flag == 1) Npassword[order++] = 'h';
                    else if (flag == 2) Cpassword[order++] = 'h';
                }
                break;
            case ALLEGRO_KEY_I:
                if (order < 20) {
                    if (flag == 0) Naccount[order++] = 't';
                    else if (flag == 1) Npassword[order++] = 't';
                    else if (flag == 2) Cpassword[order++] = 't';
                }
                break;
            case ALLEGRO_KEY_J:
                if (order < 20) {
                    if (flag == 0) Naccount[order++] = 'j';
                    else if (flag == 1) Npassword[order++] = 'j';
                    else if (flag == 2) Cpassword[order++] = 'j';
                }
                break;
            case ALLEGRO_KEY_K:
                if (order < 20) {
                    if (flag == 0) Naccount[order++] = 'k';
                    else if (flag == 1) Npassword[order++] = 'k';
                    else if (flag == 2) Cpassword[order++] = 'k';
                }
                break;
            case ALLEGRO_KEY_L:
                if (order < 20) {
                    if (flag == 0) Naccount[order++] = 'l';
                    else if (flag == 1) Npassword[order++] = 'l';
                    else if (flag == 2) Cpassword[order++] = 'l';
                }
                break;
            case ALLEGRO_KEY_M:
                if (order < 20) {
                    if (flag == 0) Naccount[order++] = 'm';
                    else if (flag == 1) Npassword[order++] = 'm';
                    else if (flag == 2) Cpassword[order++] = 'm';
                }
                break;
            case ALLEGRO_KEY_N:
                if (order < 20) {
                    if (flag == 0) Naccount[order++] = 'n';
                    else if (flag == 1) Npassword[order++] = 'n';
                    else if (flag == 2) Cpassword[order++] = 'n';
                }
                break;
            case ALLEGRO_KEY_O:
                if (order < 20) {
                    if (flag == 0) Naccount[order++] = 'o';
                    else if (flag == 1) Npassword[order++] = 'o';
                    else if (flag == 2) Cpassword[order++] = 'o';
                }
                break;
            case ALLEGRO_KEY_P:
                if (order < 20) {
                    if (flag == 0) Naccount[order++] = 'p';
                    else if (flag == 1) Npassword[order++] = 'p';
                    else if (flag == 2) Cpassword[order++] = 'p';
                }
                break;
            case ALLEGRO_KEY_Q:
                if (order < 20) {
                    if (flag == 0) Naccount[order++] = 'q';
                    else if (flag == 1) Npassword[order++] = 'q';
                    else if (flag == 2) Cpassword[order++] = 'q';
                }
                break;
            case ALLEGRO_KEY_R:
                if (order < 20) {
                    if (flag == 0) Naccount[order++] = 'r';
                    else if (flag == 1) Npassword[order++] = 'r';
                    else if (flag == 2) Cpassword[order++] = 'r';
                }
                break;
            case ALLEGRO_KEY_S:
                if (order < 20) {
                    if (flag == 0) Naccount[order++] = 's';
                    else if (flag == 1) Npassword[order++] = 's';
                    else if (flag == 2) Cpassword[order++] = 's';
                }
                break;
            case ALLEGRO_KEY_T:
                if (order < 20) {
                    if (flag == 0) Naccount[order++] = 't';
                    else if (flag == 1) Npassword[order++] = 't';
                    else if (flag == 2) Cpassword[order++] = 't';
                }
                break;
            case ALLEGRO_KEY_U:
                if (order < 20) {
                    if (flag == 0) Naccount[order++] = 'u';
                    else if (flag == 1) Npassword[order++] = 'u';
                    else if (flag == 2) Cpassword[order++] = 'u';
                }
                break;
            case ALLEGRO_KEY_V:
                if (order < 20) {
                    if (flag == 0) Naccount[order++] = 'v';
                    else if (flag == 1) Npassword[order++] = 'v';
                    else if (flag == 2) Cpassword[order++] = 'v';
                }
                break;
            case ALLEGRO_KEY_W:
                if (order < 20) {
                    if (flag == 0) Naccount[order++] = 'w';
                    else if (flag == 1) Npassword[order++] = 'w';
                    else if (flag == 2) Cpassword[order++] = 'w';
                }
                break;
            case ALLEGRO_KEY_X:
                if (order < 20) {
                    if (flag == 0) Naccount[order++] = 'x';
                    else if (flag == 1) Npassword[order++] = 'x';
                    else if (flag == 2) Cpassword[order++] = 'x';
                }
                break;
            case ALLEGRO_KEY_Y:
                if (order < 20) {
                    if (flag == 0) Naccount[order++] = 'y';
                    else if (flag == 1) Npassword[order++] = 'y';
                    else if (flag == 2) Cpassword[order++] = 'y';
                }
                break;
            case ALLEGRO_KEY_Z:
                if (order < 20) {
                    if (flag == 0) Naccount[order++] = 'z';
                    else if (flag == 1) Npassword[order++] = 'z';
                    else if (flag == 2) Cpassword[order++] = 'z';
                }
                break;
            case ALLEGRO_KEY_0:
                if (order < 20) {
                    if (flag == 0) Naccount[order++] = '0';
                    else if (flag == 1) Npassword[order++] = '0';
                    else if (flag == 2) Cpassword[order++] = '0';
                }
                break;
            case ALLEGRO_KEY_1:
                if (order < 20) {
                    if (flag == 0) Naccount[order++] = '1';
                    else if (flag == 1) Npassword[order++] = '1';
                    else if (flag == 2) Cpassword[order++] = '1';
                }
                break;
            case ALLEGRO_KEY_2:
                if (order < 20) {
                    if (flag == 0) Naccount[order++] = '2';
                    else if (flag == 1) Npassword[order++] = '2';
                    else if (flag == 2) Cpassword[order++] = '2';
                }
                break;
            case ALLEGRO_KEY_3:
                if (order < 20) {
                    if (flag == 0) Naccount[order++] = '3';
                    else if (flag == 1) Npassword[order++] = '3';
                    else if (flag == 2) Cpassword[order++] = '3';
                }
                break;
            case ALLEGRO_KEY_4:
                if (order < 20) {
                    if (flag == 0) Naccount[order++] = '4';
                    else if (flag == 1) Npassword[order++] = '4';
                    else if (flag == 2) Cpassword[order++] = '4';
                }
                break;
            case ALLEGRO_KEY_5:
                if (order < 20) {
                    if (flag == 0) Naccount[order++] = '5';
                    else if (flag == 1) Npassword[order++] = '5';
                    else if (flag == 2) Cpassword[order++] = '5';
                }
                break;
            case ALLEGRO_KEY_6:
                if (order < 20) {
                    if (flag == 0) Naccount[order++] = '6';
                    else if (flag == 1) Npassword[order++] = '6';
                    else if (flag == 2) Cpassword[order++] = '6';
                }
                break;
            case ALLEGRO_KEY_7:
                if (order < 20) {
                    if (flag == 0) Naccount[order++] = '7';
                    else if (flag == 1) Npassword[order++] = '7';
                    else if (flag == 2) Cpassword[order++] = '7';
                }
                break;
            case ALLEGRO_KEY_8:
                if (order < 20) {
                    if (flag == 0) Naccount[order++] = '8';
                    else if (flag == 1) Npassword[order++] = '8';
                    else if (flag == 2) Cpassword[order++] = '8';
                }
                break;
            case ALLEGRO_KEY_9:
                if (order < 20) {
                    if (flag == 0) Naccount[order++] = '9';
                    else if (flag == 1) Npassword[order++] = '9';
                    else if (flag == 2) Cpassword[order++] = '9';
                }
                break;
         }
    }
    else if(event.type == ALLEGRO_EVENT_MOUSE_AXES) {
        mouse_x = event.mouse.x;
        mouse_y = event.mouse.y;
    }

    if (redraw) {
        al_clear_to_color(al_map_rgb(255,255,255));

        al_draw_text(create, al_map_rgb(0,0,0),250,100,ALLEGRO_ALIGN_RIGHT,"New Account:");
        al_draw_text(create, al_map_rgb(0,0,0),250,150,ALLEGRO_ALIGN_RIGHT,"New Password:");
        al_draw_text(create, al_map_rgb(0,0,0),250,200,ALLEGRO_ALIGN_RIGHT,"Confirm Password:");

        al_draw_line(250,120,450,120,al_map_rgb(0,0,0),3);
        al_draw_line(250,170,450,170,al_map_rgb(0,0,0),3);
        al_draw_line(250,220,450,220,al_map_rgb(0,0,0),3);

        if (flag == 0) {
            al_draw_textf(sign, al_map_rgb(0,0,0), 250, 100, ALLEGRO_ALIGN_LEFT, "%s", Naccount);
            al_draw_line(251+(order)*8, 120, 259+(order)*8, 120, al_map_rgb(255, 125, 125), 2);

        }
        else if (flag == 1) {
            al_draw_textf(sign, al_map_rgb(0,0,0), 250, 100, ALLEGRO_ALIGN_LEFT, "%s", Naccount);
            al_draw_textf(sign, al_map_rgb(0,0,0), 250, 150, ALLEGRO_ALIGN_LEFT, "%s", Npassword);
            al_draw_line(251+(order)*8, 170, 259+(order)*8, 170, al_map_rgb(255, 125, 125), 2);
        }
        else if (flag == 2) {
            al_draw_textf(sign, al_map_rgb(0,0,0), 250, 100, ALLEGRO_ALIGN_LEFT, "%s", Naccount);
            al_draw_textf(sign, al_map_rgb(0,0,0), 250, 150, ALLEGRO_ALIGN_LEFT, "%s", Npassword);
            al_draw_textf(sign, al_map_rgb(0,0,0), 250, 200, ALLEGRO_ALIGN_LEFT, "%s", Cpassword);
            al_draw_line(251+(order)*8, 220, 259+(order)*8, 220, al_map_rgb(255, 125, 125), 2);
        }
        else if (flag == 3) {
            al_draw_textf(sign, al_map_rgb(0,0,0), 250, 100, ALLEGRO_ALIGN_LEFT, "%s", Naccount);
            al_draw_textf(sign, al_map_rgb(0,0,0), 250, 150, ALLEGRO_ALIGN_LEFT, "%s", Npassword);
            al_draw_textf(sign, al_map_rgb(0,0,0), 250, 200, ALLEGRO_ALIGN_LEFT, "%s", Cpassword);
        }

        if(mouse_x<=340 && mouse_x>=260 && mouse_y<=295 && mouse_y>=270) {
            al_draw_text(create,al_map_rgb(255,0,0),300,275,ALLEGRO_ALIGN_CENTER,"SEND");
            al_draw_rounded_rectangle(260,270,340,295,1,1,al_map_rgb(255,0,0),3);
        }
        else {
            al_draw_text(create,al_map_rgb(0,0,0),300,275,ALLEGRO_ALIGN_CENTER,"SEND");
            al_draw_rounded_rectangle(260,270,340,295,1,1,al_map_rgb(0,0,0),3);
        }

        if(mouse_x<=440 && mouse_x>=360 && mouse_y<=295 && mouse_y>=270) {
            al_draw_text(create,al_map_rgb(255,0,0),400,275,ALLEGRO_ALIGN_CENTER,"CLEAN");
            al_draw_rounded_rectangle(360,270,440,295,1,1,al_map_rgb(255,0,0),3);
        }
        else {
            al_draw_text(create,al_map_rgb(0,0,0),400,275,ALLEGRO_ALIGN_CENTER,"CLEAN");
            al_draw_rounded_rectangle(360,270,440,295,1,1,al_map_rgb(0,0,0),3);
        }

        if(mouse_x<=800 && mouse_x>=650 && mouse_y<=595 && mouse_y>=525) {
            al_draw_text(title2,al_map_rgb(255,0,0),730,530,ALLEGRO_ALIGN_CENTER,"BACK");
            al_draw_rounded_rectangle(650,525,810,595,1,1,al_map_rgb(255,0,0),3);
        }
        else {
            al_draw_text(title2,al_map_rgb(0,0,0),730,530,ALLEGRO_ALIGN_CENTER,"BACK");
            al_draw_rounded_rectangle(650,525,810,595,1,1,al_map_rgb(0,0,0),3);
        }
        al_flip_display();
    }
    return false;
}

bool
GameWindow::game_select_character()
{
    bool redraw = false;

    al_wait_for_event(event_queue, &event);

    if (event.type == ALLEGRO_EVENT_TIMER) {
        redraw = true;
    }
    else if(event.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
        game_destroy();
        exit(0);
    }
    else if(event.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN){
        if(event.mouse.button==1){
            if(ready1==0){
                if(mouse_x<= 300 && mouse_x>=280 && mouse_y<=250 && mouse_y>=220 ){
                    if(player1==2) player1=0;
                    else player1++;
                }
                else if(mouse_x<= 95 && mouse_x>=75 && mouse_y<=250 && mouse_y>=220){
                    if(player1==0) player1=2;
                    else player1--;
                }
            }
            if(ready2==0){
                if(mouse_x<= 700 && mouse_x>=680 && mouse_y<=250 && mouse_y>=220){
                    if(player2==2) player2=0;
                    else player2++;
                }
                else if(mouse_x<= 495 && mouse_x>=475 && mouse_y<=250 && mouse_y>=220){
                    if(player2==0) player2=2;
                    else player2--;
                }
            }
            if(mouse_x<= 805 && mouse_x>=650 && mouse_y<=595 && mouse_y>=525){
                printf("Exit\n");
                exit(0);
            }
        }
    }
    else if(event.type == ALLEGRO_EVENT_KEY_DOWN){
        if(event.keyboard.keycode == ALLEGRO_KEY_ENTER){
            if(ready1==1 && ready2==1) {
                P1 = player1;
                P2 = player2;
                return true;
            }
            else if(ready1==1 && ready2==0)
                printf("Player 2 is not ready!\n");
            else if(ready1==0 && ready2==1)
                printf("Player 1 is not ready!\n");
            else
                printf("Both two players are not ready!\n");
        }
        else if(event.keyboard.keycode == ALLEGRO_KEY_RSHIFT){
            ready1=1;
            printf("Player 1 is ready!\n");
        }
        else if(event.keyboard.keycode == ALLEGRO_KEY_LSHIFT){
            ready2=1;
            printf("Player 2 is ready!\n");
        }
    }
    else if(event.type == ALLEGRO_EVENT_MOUSE_AXES){
        mouse_x=event.mouse.x;
        mouse_y=event.mouse.y;
    }

    if (redraw) {
        al_clear_to_color(al_map_rgb(100,100,100));
        al_draw_bitmap(background1,0,0,0);if(mouse_x<=800 && mouse_x>=650 && mouse_y<=595 && mouse_y>=525) {
            al_draw_text(title2,al_map_rgb(255,0,0),730,530,ALLEGRO_ALIGN_CENTER,"EXIT");
            al_draw_rounded_rectangle(650,525,810,595,1,1,al_map_rgb(255,0,0),3);
        }
        else {
            al_draw_text(title2,al_map_rgb(255,255,255),730,530,ALLEGRO_ALIGN_CENTER,"EXIT");
            al_draw_rounded_rectangle(650,525,810,595,1,1,al_map_rgb(255,255,255),3);
        }
        al_draw_text(title2,al_map_rgb(255,255,0),200,70,ALLEGRO_ALIGN_CENTER,"PLAYER 1");
        al_draw_text(title2,al_map_rgb(255,255,0),600,70,ALLEGRO_ALIGN_CENTER,"PLAYER 2");
        al_draw_text(title3,al_map_rgb(255,255,0),110,350,ALLEGRO_ALIGN_CENTER,"Power:");
        al_draw_text(title3,al_map_rgb(255,255,0),110,400,ALLEGRO_ALIGN_CENTER,"Quantity:");
        al_draw_text(title3,al_map_rgb(255,255,0),110,450,ALLEGRO_ALIGN_CENTER,"Speed:");
        al_draw_text(title3,al_map_rgb(255,255,0),560,350,ALLEGRO_ALIGN_CENTER,"Power:");
        al_draw_text(title3,al_map_rgb(255,255,0),560,400,ALLEGRO_ALIGN_CENTER,"Quantity:");
        al_draw_text(title3,al_map_rgb(255,255,0),560,450,ALLEGRO_ALIGN_CENTER,"Speed:");

        if (player1 == LANBO) {
            al_draw_filled_rectangle(165,361,205,381,al_map_rgb(255,0,0));
            al_draw_rounded_rectangle(165,361,265,381,1,1,al_map_rgb(0,0,0),1);

            al_draw_filled_rectangle(190,411,230,431,al_map_rgb(255,0,0));
            al_draw_rounded_rectangle(190,411,290,431,1,1,al_map_rgb(0,0,0),1);

            al_draw_filled_rectangle(165,461,205,481,al_map_rgb(255,0,0));
            al_draw_rounded_rectangle(165,461,265,481,1,1,al_map_rgb(0,0,0),1);
        }
        else if (player1 == KUNBO) {
            al_draw_filled_rectangle(165,361,185,381,al_map_rgb(255,0,0));
            al_draw_rounded_rectangle(165,361,265,381,1,1,al_map_rgb(0,0,0),1);

            al_draw_filled_rectangle(190,411,210,431,al_map_rgb(255,0,0));
            al_draw_rounded_rectangle(190,411,290,431,1,1,al_map_rgb(0,0,0),1);

            al_draw_filled_rectangle(165,461,245,481,al_map_rgb(255,0,0));
            al_draw_rounded_rectangle(165,461,265,481,1,1,al_map_rgb(0,0,0),1);
        }
        else if (player1 == ININ) {
            al_draw_filled_rectangle(165,361,225,381,al_map_rgb(255,0,0));
            al_draw_rounded_rectangle(165,361,265,381,1,1,al_map_rgb(0,0,0),1);

            al_draw_filled_rectangle(190,411,210,431,al_map_rgb(255,0,0));
            al_draw_rounded_rectangle(190,411,290,431,1,1,al_map_rgb(0,0,0),1);

            al_draw_filled_rectangle(165,461,205,481,al_map_rgb(255,0,0));
            al_draw_rounded_rectangle(165,461,265,481,1,1,al_map_rgb(0,0,0),1);
        }

        if (player2 == LANBO) {
            al_draw_filled_rectangle(615,361,655,381,al_map_rgb(255,0,0));
            al_draw_rounded_rectangle(615,361,715,381,1,1,al_map_rgb(0,0,0),1);

            al_draw_filled_rectangle(640,411,680,431,al_map_rgb(255,0,0));
            al_draw_rounded_rectangle(640,411,740,431,1,1,al_map_rgb(0,0,0),1);

            al_draw_filled_rectangle(617,461,657,481,al_map_rgb(255,0,0));
            al_draw_rounded_rectangle(617,461,717,481,1,1,al_map_rgb(0,0,0),1);
        }
        else if (player2 == KUNBO) {
            al_draw_filled_rectangle(615,361,635,381,al_map_rgb(255,0,0));
            al_draw_rounded_rectangle(615,361,715,381,1,1,al_map_rgb(0,0,0),1);

            al_draw_filled_rectangle(640,411,660,431,al_map_rgb(255,0,0));
            al_draw_rounded_rectangle(640,411,740,431,1,1,al_map_rgb(0,0,0),1);

            al_draw_filled_rectangle(617,461,697,481,al_map_rgb(255,0,0));
            al_draw_rounded_rectangle(617,461,717,481,1,1,al_map_rgb(0,0,0),1);
        }
        else if (player2 == ININ) {
            al_draw_filled_rectangle(615,361,675,381,al_map_rgb(255,0,0));
            al_draw_rounded_rectangle(615,361,715,381,1,1,al_map_rgb(0,0,0),1);

            al_draw_filled_rectangle(640,411,660,431,al_map_rgb(255,0,0));
            al_draw_rounded_rectangle(640,411,740,431,1,1,al_map_rgb(0,0,0),1);

            al_draw_filled_rectangle(617,461,657,481,al_map_rgb(255,0,0));
            al_draw_rounded_rectangle(617,461,717,481,1,1,al_map_rgb(0,0,0),1);
        }
        for (int i = 0 ; i < 4 ; i++) {
            al_draw_line(185+i*20,361,185+i*20,381,al_map_rgb(0,0,0),1);
            al_draw_line(210+i*20,411,210+i*20,431,al_map_rgb(0,0,0),1);
            al_draw_line(185+i*20,461,185+i*20,481,al_map_rgb(0,0,0),1);
            al_draw_line(635+i*20,361,635+i*20,381,al_map_rgb(0,0,0),1);
            al_draw_line(660+i*20,411,660+i*20,431,al_map_rgb(0,0,0),1);
            al_draw_line(637+i*20,461,637+i*20,481,al_map_rgb(0,0,0),1);
        }

        if(player1 == LANBO)
            al_draw_bitmap(character[LANBO],110,170,0);
        else if(player1 == KUNBO)
            al_draw_bitmap(character[KUNBO],124,165,0);
        else if(player1 == ININ)
            al_draw_bitmap(character[ININ],134,175,0);
        if(player2 == LANBO)
            al_draw_bitmap(character[LANBO],510,170,0);
        else if(player2 == KUNBO)
            al_draw_bitmap(character[KUNBO],524,165,0);
        else if(player2 == ININ)
            al_draw_bitmap(character[ININ],534,175,0);

        if(ready1)
            al_draw_rounded_rectangle(110,170,265,300,1,1,al_map_rgb(255,0,0),2);
        else
            al_draw_rounded_rectangle(110,170,265,300,1,1,al_map_rgb(255,255,255),2);
        if(ready2)
            al_draw_rounded_rectangle(510,170,665,300,1,1,al_map_rgb(255,0,0),2);
        else
            al_draw_rounded_rectangle(510,170,665,300,1,1,al_map_rgb(255,255,255),2);

        if(mouse_x<=300 && mouse_x>=280 && mouse_y<=250 && mouse_y>=220 && !ready1){
            al_draw_filled_triangle(280,220,280,250,300,235,al_map_rgb(255,0,0));
            al_draw_filled_triangle(95,220,95,250,75,235,al_map_rgb(255,255,255));
            al_draw_filled_triangle(680,220,680,250,700,235,al_map_rgb(255,255,255));
            al_draw_filled_triangle(495,220,495,250,475,235,al_map_rgb(255,255,255));
        }
        else if(mouse_x<=95 && mouse_x>=75 && mouse_y<=250 && mouse_y>=220 && !ready1){
            al_draw_filled_triangle(280,220,280,250,300,235,al_map_rgb(255,255,255));
            al_draw_filled_triangle(95,220,95,250,75,235,al_map_rgb(255,0,0));
            al_draw_filled_triangle(680,220,680,250,700,235,al_map_rgb(255,255,255));
            al_draw_filled_triangle(495,220,495,250,475,235,al_map_rgb(255,255,255));
        }
        else if(mouse_x<=700 && mouse_x>=680 && mouse_y<=250 && mouse_y>=220 && !ready2){
            al_draw_filled_triangle(280,220,280,250,300,235,al_map_rgb(255,255,255));
            al_draw_filled_triangle(95,220,95,250,75,235,al_map_rgb(255,255,255));
            al_draw_filled_triangle(680,220,680,250,700,235,al_map_rgb(255,0,0));
            al_draw_filled_triangle(495,220,495,250,475,235,al_map_rgb(255,255,255));
        }
        else if(mouse_x<=495 && mouse_x>=475 && mouse_y<=250 && mouse_y>=220 && !ready2){
            al_draw_filled_triangle(280,220,280,250,300,235,al_map_rgb(255,255,255));
            al_draw_filled_triangle(95,220,95,250,75,235,al_map_rgb(255,255,255));
            al_draw_filled_triangle(680,220,680,250,700,235,al_map_rgb(255,255,255));
            al_draw_filled_triangle(495,220,495,250,475,235,al_map_rgb(255,0,0));
        }
        else{
            al_draw_filled_triangle(280,220,280,250,300,235,al_map_rgb(255,255,255));
            al_draw_filled_triangle(95,220,95,250,75,235,al_map_rgb(255,255,255));
            al_draw_filled_triangle(680,220,680,250,700,235,al_map_rgb(255,255,255));
            al_draw_filled_triangle(495,220,495,250,475,235,al_map_rgb(255,255,255));
        }
        if(mouse_x<=800 && mouse_x>=650 && mouse_y<=595 && mouse_y>=525) {
            al_draw_text(title2,al_map_rgb(255,0,0),730,530,ALLEGRO_ALIGN_CENTER,"EXIT");
            al_draw_rounded_rectangle(650,525,810,595,1,1,al_map_rgb(255,0,0),3);
        }
        else {
            al_draw_text(title2,al_map_rgb(255,255,255),730,530,ALLEGRO_ALIGN_CENTER,"EXIT");
            al_draw_rounded_rectangle(650,525,810,595,1,1,al_map_rgb(255,255,255),3);
        }
        al_flip_display();
    }
    return false;
}

bool
GameWindow::game_select_map()
{
    bool redraw = false;

    al_wait_for_event(event_queue, &event);

    if (event.type == ALLEGRO_EVENT_TIMER) {
        redraw = true;
    }
    else if(event.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
        game_destroy();
        exit(0);
    }
    else if(event.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN){
        if(event.mouse.button==1){
            if(mouse_x<= 235 && mouse_x>=215 && mouse_y<=404 && mouse_y>=374){
                if(selectMap==0) selectMap = 2;
                else selectMap--;
            }
            else if(mouse_x<= 585 && mouse_x>=565 && mouse_y<=404 && mouse_y>=374){
                if(selectMap==2) selectMap = 0;
                else selectMap++;
            }
            if(mouse_x<= 805 && mouse_x>=650 && mouse_y<=595 && mouse_y>=525){
                game_destroy();
                exit(0);
            }
        }
    }
    else if(event.type == ALLEGRO_EVENT_KEY_DOWN){
        if(event.keyboard.keycode == ALLEGRO_KEY_ENTER) {
            level = new MAP(selectMap);
            al_stop_sample_instance(homesound);

            char buffer[50];
            sprintf(buffer, "map%d.wav", selectMap);
            sample = al_load_sample(buffer);
            mapsound = al_create_sample_instance(sample);
            al_set_sample_instance_playmode(mapsound, ALLEGRO_PLAYMODE_LOOP);
            al_attach_sample_instance_to_mixer(mapsound, al_get_default_mixer());
            al_play_sample_instance(mapsound);
            return true;
        }
    }
    else if(event.type == ALLEGRO_EVENT_MOUSE_AXES){
        mouse_x=event.mouse.x;
        mouse_y=event.mouse.y;
    }

    if (redraw) {
        al_clear_to_color(al_map_rgb(100,100,100));
        al_draw_bitmap(background2,0,0,0);
        al_draw_text(title,al_map_rgb(255,255,0),400,100,ALLEGRO_ALIGN_CENTER,"Choose Map");


        al_draw_bitmap(Map[selectMap],250,250,0);
        al_draw_rounded_rectangle(250,250,550,527,2,2,al_map_rgb(255,255,255),2);

        if(mouse_x<=235 && mouse_x>=215 && mouse_y<=404 && mouse_y>=374){
            al_draw_filled_triangle(235,404,235,374,215,389,al_map_rgb(255,0,0));
            al_draw_filled_triangle(565,404,565,374,585,389,al_map_rgb(255,255,255));
        }
        else if(mouse_x<=585 && mouse_x>=565 && mouse_y<=404 && mouse_y>=374){
            al_draw_filled_triangle(235,404,235,374,215,389,al_map_rgb(255,255,255));
            al_draw_filled_triangle(565,404,565,374,585,389,al_map_rgb(255,0,0));
        }
        else{
            al_draw_filled_triangle(235,404,235,374,215,389,al_map_rgb(255,255,255));
            al_draw_filled_triangle(565,404,565,374,585,389,al_map_rgb(255,255,255));
        }
        if(mouse_x<=800 && mouse_x>=650 && mouse_y<=595 && mouse_y>=525) {
            al_draw_text(title2,al_map_rgb(255,0,0),730,530,ALLEGRO_ALIGN_CENTER,"EXIT");
            al_draw_rounded_rectangle(650,525,810,595,1,1,al_map_rgb(255,0,0),3);
        }
        else {
            al_draw_text(title2,al_map_rgb(255,255,255),730,530,ALLEGRO_ALIGN_CENTER,"EXIT");
            al_draw_rounded_rectangle(650,525,810,595,1,1,al_map_rgb(255,255,255),3);
        }

        al_flip_display();
    }
    return false;
}

bool
GameWindow::game_setting()
{/*
    static Slider background(300, 250);
    background.set_label_content("Background Music");

    al_wait_for_event(event_queue, &event);
    static int flag_button = 0;
    bool redraw = false;
    if (event.type == ALLEGRO_EVENT_TIMER) {
        redraw = true;
    }
    else if (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
        game_destroy();
        exit(0);
    }
    else if (event.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN) {
        if (event.mouse.button == 1)
            else if (mouse_hover(550, 475, 200, 50) && !background.isDragged() && !effect.isDragged()) {
                return true;
            }
            else if (background.isClicked(event.mouse.x, event.mouse.y) && !effect.isDragged()) {
                flag_button = 3;
                background.toggleDrag();
            }

    }
    else if (event.type == ALLEGRO_EVENT_MOUSE_AXES) {
        mouse_x = event.mouse.x;
        mouse_y = event.mouse.y;
        else if (mouse_hover(550, 475, 200, 50) && !background.isDragged() && !effect.isDragged()) {
            flag_button = 2;
        }
        else if (background.isDragged()) {
            flag_button = 3;
            al_set_sample_instance_gain(backgroundSound, background.Drag(event.mouse.x, event.mouse.y));
        }
        else
            flag_button = 0;
    }

    if (redraw) {
        al_clear_to_color(al_map_rgb(0, 200, 200));
        al_draw_text(font_start_scene, al_map_rgb(0,0,0), 400, 100, ALLEGRO_ALIGN_CENTER, "VOLUME");

        if (flag_button == 0) {
            al_draw_filled_rectangle(550, 475, 750, 525, al_map_rgb(150, 10, 10));
            background.set_color(al_map_rgb(0,0,0));
        }
        else if (flag_button == 2) {
            al_draw_filled_rectangle(550, 475, 750, 525, al_map_rgb(250, 0, 0));
            background.set_color(al_map_rgb(0,0,0));
        }
        else if (flag_button == 3) {
            if(!playing) al_draw_filled_rectangle(550, 375, 750, 425, al_map_rgb(150, 10, 10));
            al_draw_filled_rectangle(550, 475, 750, 525, al_map_rgb(150, 10, 10));
            background.set_color(al_map_rgb(255,0,255));
        }

        al_draw_text(font_start_scene, al_map_rgb(0,0,0), 600, 500, ALLEGRO_ALIGN_LEFT, "   BACK");

        background.Draw();
        al_flip_display();
        redraw = false;
    }

    return false;*/
}

void
GameWindow::game_begin()
{
    printf(">>> Start Map[%d]\n", level->getMap());
    Player1 = create_char(P1, 0);
    Player2 = create_char(P2, 1);

    //al_play_sample_instance(startSound);
    //while(al_get_sample_instance_playing(startSound));
    //al_play_sample_instance(backgroundSound);

    al_start_timer(playing_timer);
}
bool
GameWindow::game_run()
{
    Time = (int)al_get_time();
    if (((int)al_get_time())%1800 != 0) return process_event();
    else return true;
}

bool
GameWindow::game_endding()
{
    bool redraw = false;

    al_wait_for_event(event_queue, &event);

    if (event.type == ALLEGRO_EVENT_TIMER) {
        redraw = true;
    }
    else if(event.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
        game_destroy();
        exit(0);
    }
    else if(event.type == ALLEGRO_EVENT_KEY_DOWN){
        if(event.keyboard.keycode == ALLEGRO_KEY_ENTER) {
            return true;
        }
    }

    if (redraw) {
        al_clear_to_color(al_map_rgb(150,150,150));

        if (Player1->stop && !Player2->stop) {
            al_draw_filled_rectangle(400,0,800,600,al_map_rgb(255,100,100));
            al_draw_text(title3,al_map_rgb(255,255,0),200,350,ALLEGRO_ALIGN_CENTER,"Player 1");
            al_draw_text(title3,al_map_rgb(255,255,0),600,350,ALLEGRO_ALIGN_CENTER,"Player 2");

            al_draw_text(endding,al_map_rgb(0,0,0),200,70,ALLEGRO_ALIGN_CENTER,"LOSER");
            al_draw_text(endding,al_map_rgb(255,0,0),600,70,ALLEGRO_ALIGN_CENTER,"WINNER");
        }
        else if (!Player1->stop && Player2->stop) {
            al_draw_filled_rectangle(0,0,400,600,al_map_rgb(255,100,100));
            al_draw_text(title3,al_map_rgb(255,255,0),200,350,ALLEGRO_ALIGN_CENTER,"Player 1");
            al_draw_text(title3,al_map_rgb(255,255,0),600,350,ALLEGRO_ALIGN_CENTER,"Player 2");

            al_draw_text(endding,al_map_rgb(255,0,0),200,70,ALLEGRO_ALIGN_CENTER,"WINNER");
            al_draw_text(endding,al_map_rgb(0,0,0),600,70,ALLEGRO_ALIGN_CENTER,"LOSER");
        }
        else {
            al_draw_text(title3,al_map_rgb(255,255,0),200,350,ALLEGRO_ALIGN_CENTER,"Player 1");
            al_draw_text(title3,al_map_rgb(255,255,0),600,350,ALLEGRO_ALIGN_CENTER,"Player 2");

            al_draw_text(endding,al_map_rgb(255,255,0),200,70,ALLEGRO_ALIGN_CENTER,"DRAW");
            al_draw_text(endding,al_map_rgb(255,255,0),600,70,ALLEGRO_ALIGN_CENTER,"DRAW");
        }
        if(P1 == LANBO)
            al_draw_bitmap(character[LANBO],110,170,0);
        else if(P1 == KUNBO)
            al_draw_bitmap(character[KUNBO],124,165,0);
        else if(P1 == ININ)
            al_draw_bitmap(character[ININ],134,175,0);
        if(P2 == LANBO)
            al_draw_bitmap(character[LANBO],510,170,0);
        else if(P2 == KUNBO)
            al_draw_bitmap(character[KUNBO],524,165,0);
        else if(P2 == ININ)
            al_draw_bitmap(character[ININ],534,175,0);

        al_draw_bitmap(background3,0,350,0);

        al_draw_text(title3,al_map_rgb(255,255,255),610,500,ALLEGRO_ALIGN_RIGHT,"Press");
        al_draw_text(title3,al_map_rgb(255,255,255),660,550,ALLEGRO_ALIGN_CENTER,"Enter to Continue");

        al_flip_display();
    }
    return false;
}

void
GameWindow::draw_running_map()
{
    al_clear_to_color(al_map_rgb(0, 0, 0));

    al_draw_text(time, al_map_rgb(255,255,255), 790, 100, ALLEGRO_ALIGN_RIGHT, "TIME");
    al_draw_textf(time, al_map_rgb(255,255,255), 730, 300, ALLEGRO_ALIGN_RIGHT, "%d:", 2-Time/60 );
    al_draw_textf(time, al_map_rgb(255,255,255), 730, 300, ALLEGRO_ALIGN_LEFT, "%d", 60-Time%60 );

    level->Draw();
    if (Player1->push[2] != 5) if (level->push(Player1->push[0], Player1->push[1], Player1->push[2])) Player1->push[2] = 5;
    if (Player2->push[2] != 5) if (level->push(Player2->push[0], Player2->push[1], Player2->push[2])) Player2->push[2] = 5;
    Player1->Draw(level);
    Player2->Draw(level);

    al_draw_filled_rectangle(0, 585, 676, 586, al_map_rgb(0,0,250));
    al_draw_filled_rectangle(675, 0, 676, 586, al_map_rgb(0,0,250));
    al_draw_filled_rectangle(0, 586, 677, 587, al_map_rgb(50,50,250));
    al_draw_filled_rectangle(676, 0, 677, 587, al_map_rgb(50,50,250));
    al_draw_filled_rectangle(0, 587, 678, 588, al_map_rgb(150,150,250));
    al_draw_filled_rectangle(677, 0, 678, 588, al_map_rgb(150,150,250));
    al_draw_filled_rectangle(0, 588, 679, 589, al_map_rgb(200,200,250));
    al_draw_filled_rectangle(678, 0, 679, 589, al_map_rgb(200,200,250));
    al_draw_filled_rectangle(0, 589, 680, 590, al_map_rgb(250,250,250));
    al_draw_filled_rectangle(679, 0, 680, 590, al_map_rgb(250,250,250));
    al_flip_display();
}
int
GameWindow::process_event()
{
    bool redraw = false;

    al_wait_for_event(event_queue, &event);

    if (event.type == ALLEGRO_EVENT_TIMER) {
        redraw = true;
    }
    else if(event.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
        game_destroy();
        exit(0);
    }
    else if(event.type == ALLEGRO_EVENT_KEY_DOWN && (!Player1->stop && !Player2->stop)) {
        switch (event.keyboard.keycode) {
            case ALLEGRO_KEY_LEFT:      ///player1
                move1[LEFT] = true;
                break;
            case ALLEGRO_KEY_RIGHT:
                move1[RIGHT] = true;
                break;
            case ALLEGRO_KEY_UP:
                move1[UP] = true;
                break;
            case ALLEGRO_KEY_DOWN:
                move1[DOWN] = true;
                break;
            case ALLEGRO_KEY_RCTRL:    ///place waterball
                if (Player1->waterball_valid())
                    Player1->place_waterball();
                break;
        }
        switch (event.keyboard.keycode) {
            case ALLEGRO_KEY_A:         ///player2
                move2[LEFT] = true;
                break;
            case ALLEGRO_KEY_D:
                move2[RIGHT] = true;
                break;
            case ALLEGRO_KEY_W:
                move2[UP] = true;
                break;
            case ALLEGRO_KEY_S:
                move2[DOWN] = true;
                break;
            case ALLEGRO_KEY_LCTRL:    ///place waterball
                if (Player2->waterball_valid())
                    Player2->place_waterball();
                break;
        }
    }
    else if(event.type == ALLEGRO_EVENT_KEY_UP && (!Player1->stop && !Player2->stop)) {
        switch (event.keyboard.keycode) {
            case ALLEGRO_KEY_LEFT:      ///player1
                move1[LEFT] = false;
                break;
            case ALLEGRO_KEY_RIGHT:
                move1[RIGHT] = false;
                break;
            case ALLEGRO_KEY_UP:
                move1[UP] = false;
                break;
            case ALLEGRO_KEY_DOWN:
                move1[DOWN] = false;
                break;
        }
        switch (event.keyboard.keycode) {
            case ALLEGRO_KEY_A:         ///player2
                move2[LEFT] = false;
                break;
            case ALLEGRO_KEY_D:
                move2[RIGHT] = false;
                break;
            case ALLEGRO_KEY_W:
                move2[UP] = false;
                break;
            case ALLEGRO_KEY_S:
                move2[DOWN] = false;
                break;
        }
    }

    if(redraw) {
        Player1->be_attacked(level);
        Player2->be_attacked(level);

        if (!Player1->is_attacked) {
            if (move1[LEFT]) Player1->move(LEFT, level);
            else if (move1[RIGHT]) Player1->move(RIGHT, level);
            if (move1[UP]) Player1->move(UP, level);
            else if (move1[DOWN]) Player1->move(DOWN, level);
        }
        if (!Player2->is_attacked) {
            if (move2[LEFT]) Player2->move(LEFT, level);
            else if (move2[RIGHT]) Player2->move(RIGHT, level);
            if (move2[UP]) Player2->move(UP, level);
            else if (move2[DOWN]) Player2->move(DOWN, level);
        }

        draw_running_map();
        redraw = false;
    }

    if (Player1->die || Player2->die) return true;
    else return false;
}

void
GameWindow::game_destroy()
{
    al_destroy_display(display);
    al_destroy_event_queue(event_queue);

    al_destroy_timer(timer);
    al_destroy_timer(playing_timer);

    al_destroy_bitmap(icon);
    al_destroy_bitmap(start);
    al_destroy_bitmap(sign_in);
    al_destroy_bitmap(confirm);
    al_destroy_bitmap(background1);
    al_destroy_bitmap(background2);
    al_destroy_bitmap(background3);
    for (int i = 0 ; i < Num_CharacterType ; i++)
        al_destroy_bitmap(character[i]);
    for (int i = 0 ; i < Num_MapType ; i++)
        al_destroy_bitmap(Map[i]);

    al_destroy_font(title);
    al_destroy_font(title2);
    al_destroy_font(title3);
    al_destroy_font(endding);
    al_destroy_font(sign);
    al_destroy_font(create);

    al_destroy_sample(sample);
    al_destroy_sample_instance(homesound);
    //al_destroy_sample_instance(Play);

    delete level;
}

Character*
GameWindow::create_char(int type, int num) {
    Character *t;
    switch(type) {
        case LANBO:
            t = new Lanbo(level->get_player_index(num)%15*45, level->get_player_index(num)/15*45);
            break;
        case KUNBO:
            t = new Kunbo(level->get_player_index(num)%15*45, level->get_player_index(num)/15*45);
            break;
        case ININ:
            t = new Inin(level->get_player_index(num)%15*45, level->get_player_index(num)/15*45);
            break;
        default:
            break;
    }
    return t;
};
