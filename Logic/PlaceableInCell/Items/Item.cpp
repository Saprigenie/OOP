#include "Item.h"

Item::Item(int id, Pos curr_pos): PlaceableInCell(id, curr_pos, 1) {}

Interactions Item::Interact(PlaceableInCell* to) {
    auto res = to->Interact(*this);
    return res;
};

Interactions Item::Interact(Enemy& to) {
    to.Interact(*this);
    return kE_interact_I;
}

Interactions Item::Interact(Item& to) {
    return kI_interact_I;
}

Interactions Item::Interact(Player& to) {
    Pos last_pos = this->getPos();
    curr_pos_ = to.getPos();
    to.Move(last_pos);
    return kP_interact_I;
}
