#ifndef PLACEABLEINCELL_H
#define PLACEABLEINCELL_H

#include <string>

#include "../Room/Pos.h"
#include "PlaceablesDeclaration.h"
#include "InteractionEnum.h"

class PlaceableInCell {
protected:
    int id_;
    Pos curr_pos_;
public:
    PlaceableInCell(int id, Pos curr_pos);

    Pos getPos();
    void setPos(Pos new_pos);
    int getId();

    virtual Interactions Interact(PlaceableInCell* to) = 0;
    virtual Interactions Interact(Player& to) = 0;
    virtual Interactions Interact(Enemy& to) = 0;
    virtual Interactions Interact(Item& to) = 0;

    virtual void Move(Pos new_pos = Pos{-1, -1}) = 0;
};

#endif // PLACEABLEINCELL_H
