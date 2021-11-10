#ifndef ITEM_H
#define ITEM_H

#include "../PlaceableInCell.h"
#include "../Player/Player.h"
#include "../Enemies/Enemy.h"
#include "../../Room/Pos.h"

class Item: public PlaceableInCell {
public:
    Item(int id, Pos curr_pos);

    Interactions Interact(PlaceableInCell* to);
    Interactions Interact(Enemy& to);
    virtual Interactions Interact(Player& to);
    Interactions Interact(Item& to);

    void Move(Pos new_pos = Pos{-1, -1});
};

#endif // ITEM_H
