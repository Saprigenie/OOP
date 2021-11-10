#ifndef EXITCELL_H
#define EXITCELL_H

#include "../Cell.h"

class ExitCell: public Cell  {
    int item_id_to_process_;
public:
    ExitCell(Pos cell_pos, int item_id_to_process = -1, PlaceableInCell* object_in_cell = nullptr);

    bool PlayerInteract(Player& to);
};

#endif // EXITCELL_H
