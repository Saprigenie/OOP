#include "KeyItem.h"

KeyItem::KeyItem(int id, Pos curr_pos): Item(id, curr_pos) {}

Interactions KeyItem::Interact(Player& to) {
    to.appendItem(id_);
    life_ = 0;
    return Item::Interact(to);
}
