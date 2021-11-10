#include "Cell.h"

Cell::Cell(Pos cell_pos, PlaceableInCell* object_in_cell): cell_pos_(cell_pos), object_in_cell_(object_in_cell) {}

Cell::Cell(const Cell& from) {
    object_in_cell_ = from.object_in_cell_;
}

Cell& Cell::operator =(const Cell& from) {
    if (&from != this) {
        delete object_in_cell_;
        object_in_cell_ = from.object_in_cell_;
    }
    return *this;
}

void Cell::setObject(PlaceableInCell* new_object) {
    object_in_cell_ = new_object;
}

PlaceableInCell* Cell::getObject() {
    return object_in_cell_;
}

Cell::~Cell() {
    if (object_in_cell_)
        delete object_in_cell_;
}
