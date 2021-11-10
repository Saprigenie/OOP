#include "Enemy.h"

Enemy::Enemy(int id, Pos pos, int attack, MoveStrategy* new_strategy):
PlaceableInCell(id, pos) {
    attack_ = attack;
    curr_strategy_ = new_strategy;
}

void Enemy::getDamaged(int damage) {
    life_ -= damage;
}

Interactions Enemy::Interact(PlaceableInCell* to) {
    auto res = to->Interact(*this);
    return res;
};

Interactions Enemy::Interact(Enemy& to) {
    return kE_interact_E;
}

Interactions Enemy::Interact(Player& to) {
    to.Damage_sanity(attack_);
    getDamaged(to.damage_to_enemy_);
    return kP_interact_E;
}

Interactions Enemy::Interact(Item& to) {
    Pos tmp = to.getPos();
    to.setPos(curr_pos_);
    curr_pos_ = tmp;
    return kI_interact_E;
}

void Enemy::setMoveStrategy(MoveStrategy* new_strategy) {
    curr_strategy_ = new_strategy;
}

void Enemy::Move(Pos new_pos) {
    if (new_pos.x == -1 && new_pos.y == -1)
        curr_pos_ = curr_strategy_->Move(curr_pos_);
    else
        curr_pos_ = new_pos;
}

Enemy::~Enemy() {
    delete curr_strategy_;
}
