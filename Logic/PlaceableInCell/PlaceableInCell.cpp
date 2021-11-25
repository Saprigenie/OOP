#include "PlaceableInCell.h"

PlaceableInCell::PlaceableInCell(int id, Pos curr_pos, int life) {
    id_ = id;
    curr_pos_ = curr_pos;
    life_ = life;
}

Pos PlaceableInCell::getPos() {
    return curr_pos_;
}

void PlaceableInCell::setPos(Pos new_pos) {
    curr_pos_ = new_pos;
}

int PlaceableInCell::getId() {
    return id_;
}

int PlaceableInCell::getLife() {
    return life_;
}

Interactions PlaceableInCell::Interact(Furniture& to) {
    return kNot_P_interact_F;
}

void PlaceableInCell::Move(Pos new_pos) {};
