#ifndef GAMELOGIC_H
#define GAMELOGIC_H

#include <vector>

#include <QFile>

#include "../Gui/View/Observable.h"
#include"../Logging/Loggable/Loggable.h"
#include "Room/Room.h"
#include "Room/Pos.h"
#include "PlaceableInCell/Player/Player.h"
#include "PlaceableInCell/Enemies/DamageableEnemy.h"
#include "PlaceableInCell/Enemies/LimitedLifeEnemy.h"
#include "PlaceableInCell/Enemies/ImmortalEnemy.h"
#include "PlaceableInCell/Items/SanityAffectItem.h"
#include "PlaceableInCell/Items/DamageToEnemiesItem.h"
#include "PlaceableInCell/Items/KeyItem.h"
#include "PlaceableInCell/Enemies/MoveStrategies/StrategiesEnum.h"

class GameLogic: public Observable, public Loggable {
private:
    Room* curr_room_;
    std::vector<PlaceableInCell*> room_objects_;

    std::map<MoveStrategies, MoveStrategy*> strategy_list;
public:
    GameLogic();

    void CreateRoom(int id = 1, int is_new_or_load = 0);
    void Start();

    Room& getRoom();
    std::vector<PlaceableInCell*>& getRoomObjects();

    void LoadCellObjects(QFile& obj_file);
    void MakeTurn(Pos player_pos_change);

    ~GameLogic();
};

#endif // GAMELOGIC_H
