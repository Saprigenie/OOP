#include "ImmortalEnemy.h"

ImmortalEnemy::ImmortalEnemy(int id, Pos pos, int attack, MoveStrategy* new_strategy):
Enemy(id, pos, 1, attack, new_strategy) {}

void ImmortalEnemy::getDamaged(int damage) {}


