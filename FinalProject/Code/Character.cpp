#include "Character.h"

Character::Character(int initial_x, int initial_y) {
    pos_x = initial_x;
    pos_y = initial_y;
}

Character::~Character() {
    for (int i = 0 ; i < Num_moveimg ; i++)
        al_destroy_bitmap(moveimg[i]);
    al_destroy_bitmap(isAttacked);
    al_destroy_bitmap(dead);
}

void
Character::Draw(MAP* level) {
    for(unsigned int i=0; i < this->attack_set.size(); i++) {
        this->attack_set[i]->Draw(level);
        if (this->attack_set[i]->explored) {
            if (this->attack_set[i]->explore_counter++ == this->attack_set[i]->explore_frequency) {
                attack_set[i]->returnRoad(level);
                Attack *attack = attack_set[i];
                this->attack_set.erase(this->attack_set.begin());
                i--;
                delete attack;
            }
        }
    }
    if (!is_attacked) al_draw_bitmap(moveimg[direction], pos_x, pos_y, 0);
    else {
        if (boom_counter++ >= boom_frequency*4) die = true;
        else {
            if (boom_counter >= boom_frequency*2) {
                al_draw_bitmap(dead, pos_x, pos_y, 0);
                stop = true;
            }
            else al_draw_bitmap(isAttacked, pos_x, pos_y, 0);
        }
    }
}

void
Character::Load_Move() {
    char buffer[50];

    for(int i=0; i < Num_moveimg; i++) {
        sprintf(buffer, "./%s/%s_%d.png", class_name, class_name, i);

        moveimg[i] = al_load_bitmap(buffer);
    }
    sprintf(buffer, "./%s/%s_%d.png", class_name, class_name, 4);
    isAttacked = al_load_bitmap(buffer);
    dead = al_load_bitmap("./picture/dead.png");
}

void
Character::move(int num, MAP *level) {
    direction = num;
    switch (num) {
        case LEFT:
            if (pos_x-character_speed > 0 && level->isRoad((pos_x-character_speed)/45, (pos_y+22.5)/45) /*|| level->isRoad((pos_x-1)/45, (pos_y+22.5)/45)*/ ) {
                pos_x-=character_speed;
                if ( level->isTool((pos_x)/45, (pos_y+22.5)/45) ) {
                    buff(level->isTool( (pos_x)/45, (pos_y+22.5)/45 ));
                    level->change_value_stright( (pos_x)/45, (pos_y+22.5)/45, ROAD );
                }
            }
            else {
                pos_x = (pos_x/45)*45;
                if ( level->can_be_push((pos_x+22.5)/45, (pos_y+22.5)/45, LEFT) && push[2] == 5 ) {
                    push[0] = (pos_x+22.5)/45-1;
                    push[1] = (pos_y+22.5)/45;
                    push[2] = LEFT;
                }
            }
            break;
        case RIGHT:
            if (pos_x+character_speed < 630 && level->isRoad((pos_x+character_speed+45)/45, (pos_y+22.5)/45) /*|| level->isRoad((pos_x+46)/45, (pos_y+22.5)/45)*/ ) {
                pos_x+=character_speed;
                if ( level->isTool((pos_x+45)/45, (pos_y+22.5)/45) ) {
                    buff(level->isTool( (pos_x+45)/45, (pos_y+22.5)/45 ));
                    level->change_value_stright( (pos_x+45)/45, (pos_y+22.5)/45, ROAD );
                }
            }
            else {
                pos_x = (pos_x/45)*45;
                if ( level->can_be_push((pos_x+22.5)/45, (pos_y+22.5)/45, RIGHT) && push[2] == 5 ) {
                    push[0] = (pos_x+22.5)/45+1;
                    push[1] = (pos_y+22.5)/45;
                    push[2] = RIGHT;
                }
            }
            break;
        case UP:
            if (pos_y-character_speed > 0 && level->isRoad((pos_x+22.5)/45, (pos_y-character_speed)/45) /*|| level->isRoad((pos_x+22.5)/45, (pos_y-1)/45)*/ ) {
                pos_y-=character_speed;
                if ( level->isTool((pos_x+22.5)/45, (pos_y)/45) ) {
                    buff(level->isTool( (pos_x+22.5)/45, (pos_y)/45 ));
                    level->change_value_stright( (pos_x+22.5)/45, (pos_y)/45, ROAD );
                }
            }
            else {
                pos_y = (pos_y/45)*45;
                if ( level->can_be_push((pos_x+22.5)/45, (pos_y+22.5)/45, UP) && push[2] == 5 ) {
                    push[0] = (pos_x+22.5)/45;
                    push[1] = (pos_y+22.5)/45-1;
                    push[2] = UP;
                }
            }
            break;
        case DOWN:
            if (pos_y+character_speed < 540 && level->isRoad((pos_x+22.5)/45, (pos_y+character_speed+45)/45) /*|| level->isRoad((pos_x+22.5)/45, (pos_y+46)/45)*/ ) {
                pos_y+=character_speed;
                if (level->isTool( (pos_x+22.5)/45, (pos_y+45)/45 )) {
                    buff(level->isTool( (pos_x+22.5)/45, (pos_y+45)/45 ));
                    level->change_value_stright( (pos_x+22.5)/45, (pos_y+45)/45, ROAD );
                }
            }
            else {
                pos_y = (pos_y/45)*45;
                if ( level->can_be_push((pos_x+22.5)/45, (pos_y+22.5)/45, DOWN) && push[2] == 5 ) {
                    push[0] = (pos_x+22.5)/45;
                    push[1] = (pos_y+22.5)/45+1;
                    push[2] = DOWN;
                }
            }
            break;
    }
}

bool
Character::waterball_valid() {
    return ((int)attack_set.size() < waterball_quantity) ? true : false;
}

void
Character::place_waterball() {
    Attack *attack;
    if ((int)attack_set.size() < waterball_quantity && (int)attack_set.size() <= max_waterball_quantity) {
        attack = new Attack((pos_x+23)/45, (pos_y+23)/45, waterball_power);
    }
    attack_set.push_back(attack);
}

void
Character::be_attacked(MAP *level) {
    if (level->beAttacked((pos_x+23)/45, (pos_y+23)/45)) is_attacked = true;
}

void
Character::buff(int num) {
    if (num == POWER) {
        if (waterball_power < max_waterball_power)
            waterball_power++;
    }
    else if (num == QUANTITY) {
        if (waterball_quantity < max_waterball_quantity)
            waterball_quantity++;
    }
    else if (num == SPEED) {
        character_speed += 0.5;
    }
}
