#ifndef DAMAGETOENEMIESITEM_H
#define DAMAGETOENEMIESITEM_H

#include "Item.h"
#include "../Player/Player.h"
#include "../../Room/Pos.h"

class DamageToEnemiesItem: public Item {
protected:
    int damage_to_enemies_;
public:
    DamageToEnemiesItem(int id, Pos curr_pos,int damage_to_enemies);

    Interactions Interact(Player& to);
};

#endif // DAMAGETOENEMIESITEM_H
