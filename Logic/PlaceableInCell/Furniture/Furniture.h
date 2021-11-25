#ifndef FURNITURE_H
#define FURNITURE_H

#include "../PlaceableInCell.h"

class Furniture: public PlaceableInCell {
private:
    int height_;
    int width_;
public:
    Furniture(int id, Pos curr_pos, int width, int height);

    int getWidth();
    int getHeight();

    virtual Interactions Interact(PlaceableInCell* to);
    virtual Interactions Interact(Player& to);
    virtual Interactions Interact(Enemy& to);
    virtual Interactions Interact(Item& to);
};

#endif // FURNITURE_H
