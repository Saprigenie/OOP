#ifndef GAMELOGIC_H
#define GAMELOGIC_H

#include <vector>

#include <QFile>

#include "../Gui/View/Observable.h"
#include"../Logging/Loggable/Loggable.h"
#include "../Game/RoomChangeNotify/RoomChangeObserver.h"
#include "Room/Room.h"
#include "Room/Pos.h"
#include "PlaceableInCell/Player/Player.h"
#include "PlaceableInCell/Enemies/Enemy.h"
#include "PlaceableInCell/Enemies/LimitedLifeEnemy.h"
#include "PlaceableInCell/Enemies/ImmortalEnemy.h"
#include "PlaceableInCell/Items/SanityAffectItem.h"
#include "PlaceableInCell/Items/DamageToEnemiesItem.h"
#include "PlaceableInCell/Items/KeyItem.h"
#include "PlaceableInCell/Furniture/Furniture.h"
#include "PlaceableInCell/Enemies/MoveStrategies/StrategiesEnum.h"

class GameLogic: public Observable, public Loggable {
private:
    Room* curr_room_;
    std::vector<PlaceableInCell*> room_move_obj_;
    std::vector<Furniture*> room_static_obj_;

    std::map<int, MoveStrategy*> strategy_list;

    RoomChangeObserver* room_change_obs_;
public:
    GameLogic();

    void CreateRoom(int id = 1, int prev_room_id = -1);
    void LoadRoom(Room* new_room, std::vector<PlaceableInCell*> new_room_move_obj,
                  std::vector<Furniture*> new_room_static_obj, int prev_room_id);

    Room& getRoom();
    std::vector<PlaceableInCell*>& getRoomMoveObjects();
    std::vector<Furniture*>& getRoomStaticObjects();
    void setRoomChangeObserver(RoomChangeObserver* new_obs);

    void NotifyRoomChanging(int id);
    void NotifyObjectDestRules(PlaceableInCell* destroyed_obj);
    bool NotifyCheckRules(int next_room_id);
    void LoadCellObjects(QFile& obj_file, Pos player_spawn_pos);
    void MakeTurn(Pos player_pos_change);

    ~GameLogic();
private:
    void DeletePlayer();
    void AddPlayer(Pos player_spawn_pos);
    void DeleteAllObjects();
};

#endif // GAMELOGIC_H
