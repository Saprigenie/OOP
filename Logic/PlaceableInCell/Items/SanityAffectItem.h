#ifndef SANITYAFFECTITEM_H
#define SANITYAFFECTITEM_H

#include "Item.h"
#include "../Player/Player.h"
#include "../../Room/Pos.h"

class SanityAffectItem: public Item {
protected:
    int sanity_heal_;
public:
    SanityAffectItem(int id, Pos curr_pos, int sanity_heal);

    Interactions Interact(Player& to);
};

#endif // SANITYAFFECTITEM_H
