#ifndef KEYITEM_H
#define KEYITEM_H

#include "Item.h"
#include "../Player/Player.h"
#include "../../Room/Pos.h"

class KeyItem: public Item {
public:
    KeyItem(int id, Pos curr_pos);

    Interactions Interact(Player& to);
};

#endif // KEYITEM_H
