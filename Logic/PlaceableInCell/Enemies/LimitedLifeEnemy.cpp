#include "LimitedLifeEnemy.h"

LimitedLifeEnemy::LimitedLifeEnemy(int id, Pos pos, int attack, int life, MoveStrategy* new_strategy):
    Enemy(id, pos, attack, new_strategy) {
    life_ = life;
}

void LimitedLifeEnemy::Move(Pos new_pos) {
    life_ -= 1;
    Enemy::Move(new_pos);
}
