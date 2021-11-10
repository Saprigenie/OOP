#include "DamageToEnemiesItem.h"

DamageToEnemiesItem::DamageToEnemiesItem(int id, Pos curr_pos, int damage_to_enemies):
Item(id, curr_pos) {
    damage_to_enemies_ = damage_to_enemies;
}

Interactions DamageToEnemiesItem::Interact(Player& to) {
    to.damage_to_enemy_ += damage_to_enemies_;
    to.Move(this->getPos());
    return Item::Interact(to);
}
