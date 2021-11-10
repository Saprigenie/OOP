#include "Player.h"

Player::Player():
PlaceableInCell(0, Pos{0, 0}) {
    sanity_ = 100;
    damage_to_enemy_ = 0;
}

Player* Player::hero_obj = nullptr;

Player& Player::getInstance() {
    if (hero_obj == nullptr) {
        hero_obj = new Player();
    }
    return *hero_obj;
}

void Player::setSanity(int sanity) {
    sanity_ = sanity;
}

int Player::getSanity() {
    return sanity_;
}

int Player::getNumItems() {
    return player_items_.size();
}

void Player::Damage_sanity(int damage) {
    sanity_ -= damage;
}

void Player::Heal_sanity(int heal) {
    sanity_ += heal;
    if (sanity_ > 100)
        sanity_ = 100;
}

void Player::appendItem(int new_item) {
    player_items_.push_back(new_item);
}

void Player::removeItem(int id) {
    for (auto it = player_items_.begin() ; it != player_items_.end(); ++it) {
        if (*it == id) {
            player_items_.erase(it);
            break;
        }
    }
}

bool Player::HasItem(int id) {
    auto res = std::find(player_items_.begin(), player_items_.end(), id);
    return res != player_items_.end();
}

void Player::Move(Pos new_pos) {
    if (new_pos.x != -1 || new_pos.y != -1)
        curr_pos_ = new_pos;
}

Interactions Player::Interact(PlaceableInCell* to) {
    auto res = to->Interact(*this);
    return res;
}

Interactions Player::Interact(Enemy& to) {
    to.Interact(*this);
    return kE_interact_P;
}

Interactions Player::Interact(Item& to) {
    to.Interact(*this);
    return kI_interact_P;
}

Interactions Player::Interact(Player& to) {
    return kP_interact_P;
}
