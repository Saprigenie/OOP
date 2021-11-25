#ifndef ROOMCHANGEOBSERVER_H
#define ROOMCHANGEOBSERVER_H

#include "../../Logic/PlaceableInCell/PlaceableInCell.h"

class RoomChangeObserver {
public:
    virtual void RoomChanging(int id) = 0;
    virtual void RuleUpdate(PlaceableInCell* destroyed_obj) = 0;
    virtual bool RuleCheck(int next_room_id) = 0;
};

#endif // ROOMCHANGEOBSERVER_H
