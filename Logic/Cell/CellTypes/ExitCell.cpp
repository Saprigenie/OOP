#include "ExitCell.h"

ExitCell::ExitCell(Pos cell_pos, int item_id_to_process, PlaceableInCell* object_in_cell):
Cell(cell_pos, object_in_cell) {
    item_id_to_process_ = item_id_to_process;
}

bool ExitCell::PlayerInteract(Player& to) {
    if(to.HasItem(item_id_to_process_)) {
        return true;
    } else {
        to.setPos(cell_pos_);
        return false;
    }
}
