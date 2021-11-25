#include "SanityAffectItem.h"

SanityAffectItem::SanityAffectItem(int id, Pos curr_pos, int sanity_heal):
Item(id, curr_pos) {
    sanity_heal_ = sanity_heal;
}

Interactions SanityAffectItem::Interact(Player& to) {
    to.Heal_sanity(sanity_heal_);
    life_ = 0;
    return Item::Interact(to);
}
