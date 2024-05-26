#ifndef MOUSE_H
#define MOUSE_H
#include "raylib.h"
#include "Table.h"
#include "player.h"
#include "attacks.h"
#include "flying_attack.h"
#include <cstdio>
#include <ctime>
Vector2 check_mouse(Table *field,__uint128_t*timer);
bool play_again_mouse();
void Game_over_screen(char winner, Texture2D background, Table *field);
bool Sans_fight_phase(Table *field,Player *player,Bone_attack *attack_1,Bone_attack * attack_2,int attack);
bool Papyrus_fight_phase(Table *field,Player *player,Spagetti_attack_object *attack_1,Spagetti_attack_object * attack_2,Spagetti_attack_object * attack_3,Spagetti_attack_object * attack_4,Spagetti_attack_object * attack_5,int attack);

#endif