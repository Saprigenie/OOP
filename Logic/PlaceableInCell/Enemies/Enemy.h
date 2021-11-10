#ifndef ENEMY_H
#define ENEMY_H

#include "../PlaceableInCell.h"
#include "../Player/Player.h"
#include "../Items/Item.h"
#include "MoveStrategies/MoveStrategy.h"
#include "MoveStrategies/MoveStrategyStandart.h"
#include "MoveStrategies/MoveStrategyConfusion.h"
#include "MoveStrategies/MoveStrategyChase.h"
#include "../../Room/Pos.h"

class Enemy: public PlaceableInCell {
protected:
    int attack_;
    int life_;

    MoveStrategy* curr_strategy_ = nullptr;

public:
    Enemy(int id, Pos pos, int attack, MoveStrategy* new_strategy);

    void getDamaged(int damage = 0);

    Interactions Interact(PlaceableInCell* to);
    Interactions Interact(Enemy& to);
    Interactions Interact(Player& to);
    Interactions Interact(Item& to);

    void setMoveStrategy(MoveStrategy* new_strategy);
    void Move(Pos new_pos = Pos{-1, -1});

    ~Enemy();
};

#endif // ENEMY_H
