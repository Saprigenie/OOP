#include "KeyItem.h"

KeyItem::KeyItem(int id, Pos curr_pos): Item(id, curr_pos) {}

Interactions KeyItem::Interact(Player& to) {
    to.appendItem(id_);
    to.Move(this->getPos());
    return Item::Interact(to);
}
