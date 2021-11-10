#ifndef ENTRANCECELL_H
#define ENTRANCECELL_H

#include "../Cell.h"

class EntranceCell: public Cell {
public:
    EntranceCell(Pos cell_pos, PlaceableInCell* object_in_cell = nullptr);

    bool PlayerInteract(Player& to);
};

#endif // ENTRANCECELL_H
