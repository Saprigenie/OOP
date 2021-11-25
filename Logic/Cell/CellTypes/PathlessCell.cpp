#include "PathlessCell.h"

PathlessCell::PathlessCell(Pos cell_pos, PlaceableInCell* object_in_cell):
    Cell(cell_pos, object_in_cell) {};

void PathlessCell::Interact(Player& to) {}
