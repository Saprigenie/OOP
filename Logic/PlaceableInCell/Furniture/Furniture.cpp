#include "Furniture.h"

Furniture::Furniture(int id, Pos curr_pos, int width, int height): PlaceableInCell(id, curr_pos, 1) {
    width_ = width;
    height_ = height;
}

int Furniture::getWidth() {
    return width_;
}

int Furniture::getHeight() {
    return height_;
}

Interactions Furniture::Interact(PlaceableInCell* to) {
    return to->Interact(*this);
}

Interactions Furniture::Interact(Player& to) {
    return kF_interact_P;
}

Interactions Furniture::Interact(Enemy& to) {
    return kF_interact_Not_P;
}

Interactions Furniture::Interact(Item& to) {
    return kF_interact_Not_P;
}
