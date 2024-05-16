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
bool Fight_phase(Table *field,Player *player,Attacks *attack_1,Attacks * attack_2,int attack);
bool Fight_phase_1(Table *field,Player *player,flying_attack *attack_1,flying_attack * attack_2,flying_attack * attack_3,flying_attack * attack_4,flying_attack * attack_5,int attack);