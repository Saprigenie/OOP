#include "EntranceCell.h"

EntranceCell::EntranceCell(Pos cell_pos, PlaceableInCell* object_in_cell):
    Cell(cell_pos, object_in_cell) {};

bool EntranceCell::PlayerInteract(Player& to) {
    to.setPos(cell_pos_);
    return false;
}
