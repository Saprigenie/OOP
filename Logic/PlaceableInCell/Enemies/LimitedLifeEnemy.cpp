#include "LimitedLifeEnemy.h"

LimitedLifeEnemy::LimitedLifeEnemy(int id, Pos pos, int life, int attack, MoveStrategy* new_strategy):
    Enemy(id, pos, life, attack, new_strategy) {}

void LimitedLifeEnemy::Move(Pos new_pos) {
    life_ -= 1;
    Enemy::Move(new_pos);
}
