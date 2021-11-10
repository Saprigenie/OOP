#include "PassableCell.h"

PassableCell::PassableCell(Pos cell_pos, PlaceableInCell* object_in_cell):
    Cell(cell_pos, object_in_cell) {};

bool PassableCell::PlayerInteract(Player& to) {
    to.setPos(cell_pos_);
    return false;
}
