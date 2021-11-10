#include "PlaceableInCell.h"

PlaceableInCell::PlaceableInCell(int id, Pos curr_pos) {
    id_ = id;
    curr_pos_ = curr_pos;
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
