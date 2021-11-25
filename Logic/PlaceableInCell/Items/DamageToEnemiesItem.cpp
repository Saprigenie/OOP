#include "DamageToEnemiesItem.h"

DamageToEnemiesItem::DamageToEnemiesItem(int id, Pos curr_pos, int damage_to_enemies):
Item(id, curr_pos) {
    damage_to_enemies_ = damage_to_enemies;
}

Interactions DamageToEnemiesItem::Interact(Player& to) {
    to.setDamageToEnemies(to.getDamageToEnemies() + damage_to_enemies_);
    life_ = 0;
    return Item::Interact(to);
}
