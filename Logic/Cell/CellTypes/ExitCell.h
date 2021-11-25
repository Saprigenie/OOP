#ifndef EXITCELL_H
#define EXITCELL_H

#include "../Cell.h"

class ExitCell: public Cell  {
public:
    ExitCell(Pos cell_pos, PlaceableInCell* object_in_cell = nullptr);
};

#endif // EXITCELL_H
