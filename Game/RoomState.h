#ifndef ROOMSTATE_H
#define ROOMSTATE_H

#include "../Logic/Room/Room.h"
#include "../Logic/PlaceableInCell/PlaceableInCell.h"
#include "../Logic/PlaceableInCell/Furniture/Furniture.h"

struct RoomState {
    Room* room;
    std::vector<PlaceableInCell*> room_move_obj;
    std::vector<Furniture*> room_static_obj;
};

#endif // ROOMSTATE_H
