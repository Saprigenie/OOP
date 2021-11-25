#include "EntranceCell.h"

EntranceCell::EntranceCell(Pos cell_pos, int next_room_id, PlaceableInCell* object_in_cell):
    Cell(cell_pos, object_in_cell) {
    next_room_id_ = next_room_id;
}

int EntranceCell::GetRoomId() {
    return next_room_id_;
}
