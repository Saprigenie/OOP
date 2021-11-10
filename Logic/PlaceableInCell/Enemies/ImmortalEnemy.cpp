#include "ImmortalEnemy.h"

ImmortalEnemy::ImmortalEnemy(int id, Pos pos, int attack, MoveStrategy* new_strategy):
Enemy(id, pos, attack, new_strategy) {
    life_ = 1;
}

void getDamaged(int damage = 0) {}


