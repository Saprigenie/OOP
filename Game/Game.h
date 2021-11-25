#ifndef GAME_H
#define GAME_H

#include <map>

#include "../Logic/GameLogic.h"
#include "../Logic/Controller/Controller.h"
#include "../Logic/Rule/RulesList.h"
#include "../Gui/GameView.h"
#include "RoomChangeNotify/RoomChangeObserver.h"
#include "ControllerObserver/ControllerObserver.h"
#include "RoomState.h"

template <RulesList& rules>
class Game: public RoomChangeObserver, public ControllerObserver {
    GameLogic logic_;
    GameView view_;
    Controller controller_;

    std::map<int, RoomState> load_rooms_;
public:
    Game(): view_(&logic_), controller_(this, &view_) {
        logic_.setRoomChangeObserver(this);
    }

    void Start() {
        logic_.CreateRoom();
        view_.show();
    }

    void RoomChanging(int id) {
        load_rooms_[logic_.getRoom().getId()] = RoomState{&logic_.getRoom(), logic_.getRoomMoveObjects(),logic_.getRoomStaticObjects() };
        if (load_rooms_.find(id) != load_rooms_.end()) {
            RoomState load_room = load_rooms_.at(id);
            logic_.LoadRoom(load_room.room, load_room.room_move_obj, load_room.room_static_obj, logic_.getRoom().getId());
        } else {
            logic_.CreateRoom(id, logic_.getRoom().getId());
        }
    }

    void RuleUpdate(PlaceableInCell* destroyed_obj) {
        rules.CheckRulesCondition(logic_.getRoom().getId(), destroyed_obj);
    }

    bool RuleCheck(int next_room_id) {
        rules.CheckRules(logic_.getRoom().getId(), next_room_id);
    }

    void PlayerChangePos(Pos player_pos_change) {
        logic_.MakeTurn(player_pos_change);
    }
};

#endif // GAME_H
