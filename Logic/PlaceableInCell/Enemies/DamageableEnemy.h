#ifndef DAMAGEABLEENEMY_H
#define DAMAGEABLEENEMY_H

#include "Enemy.h"
#include "MoveStrategies/MoveStrategy.h"
#include "../../Room/Pos.h"

class DamageableEnemy: public Enemy {
public:
    DamageableEnemy(int id, Pos pos, int attack, int life, MoveStrategy* new_strategy);
};

#endif // DAMAGEABLEENEMY_H
