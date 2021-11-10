#ifndef LIMITEDLIFEENEMY_H
#define LIMITEDLIFEENEMY_H

#include "Enemy.h"
#include "MoveStrategies/MoveStrategy.h"
#include "../../Room/Pos.h"

class LimitedLifeEnemy: public Enemy {
public:
    LimitedLifeEnemy(int id, Pos pos, int attack, int life, MoveStrategy* new_strategy);

    void Move(Pos new_pos = Pos{-1, -1});
};

#endif // LIMITEDLIFEENEMY_H
