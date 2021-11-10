#include "DamageableEnemy.h"

DamageableEnemy::DamageableEnemy(int id, Pos pos, int attack, int life, MoveStrategy* new_strategy):
Enemy(id, pos, attack, new_strategy) {
    life_ = life;
}
