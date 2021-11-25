#ifndef ENTRANCECELL_H
#define ENTRANCECELL_H

#include "../Cell.h"

class EntranceCell: public Cell {
    int next_room_id_;
public:
    EntranceCell(Pos cell_pos, int next_room_id, PlaceableInCell* object_in_cell = nullptr);

    int GetRoomId();
};

#endif // ENTRANCECELL_H
