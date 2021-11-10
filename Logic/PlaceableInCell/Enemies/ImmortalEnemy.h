#ifndef IMMORTALENEMY_H
#define IMMORTALENEMY_H

#include "Enemy.h"
#include "MoveStrategies/MoveStrategy.h"
#include "../../Room/Pos.h"

class ImmortalEnemy: public Enemy {
public:
    ImmortalEnemy(int id, Pos pos, int attack, MoveStrategy* new_strategy);

    void getDamaged(int damage = 0);
};

#endif // IMMORTALENEMY_H
