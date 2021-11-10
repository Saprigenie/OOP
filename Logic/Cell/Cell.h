#ifndef CELL_H
#define CELL_H

#include "../PlaceableInCell/PlaceableInCell.h"
#include "../PlaceableInCell/Player/Player.h"
#include "../Room/Pos.h"

class Cell {
protected:
    PlaceableInCell* object_in_cell_;
    Pos cell_pos_;

public:
    Cell(Pos cell_pos, PlaceableInCell* object_in_cell = nullptr);
    Cell(const Cell& from);
    Cell& operator =(const Cell& from);

    void setObject(PlaceableInCell* new_object);
    PlaceableInCell* getObject();

    virtual bool PlayerInteract(Player& to) = 0;

    ~Cell();
};

#endif // CELL_H
