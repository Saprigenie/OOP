#ifndef PATHLESSCELL_H
#define PATHLESSCELL_H

#include "../Cell.h"

class PathlessCell: public Cell {
public:
    PathlessCell(Pos cell_pos, PlaceableInCell* object_in_cell = nullptr);

    void Interact(Player& to);
};

#endif // PATHLESSCELL_H
