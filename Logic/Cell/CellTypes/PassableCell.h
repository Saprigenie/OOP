#ifndef PASSABLECELL_H
#define PASSABLECELL_H

#include "../Cell.h"

class PassableCell: public Cell {
public:
    PassableCell(Pos cell_pos, PlaceableInCell* object_in_cell = nullptr);
};

#endif // PASSABLECELL_H
