#include "Item.h"

Item::Item(int id, Pos curr_pos): PlaceableInCell(id, curr_pos) {}

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
    return kP_interact_I;
}

void Item::Move(Pos new_pos) {};
