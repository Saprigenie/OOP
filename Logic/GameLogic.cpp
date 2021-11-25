#include "GameLogic.h"

GameLogic::GameLogic() {
    strategy_list[kStandart] = new MoveStrategyStandart();
    strategy_list[kChase] = new MoveStrategyChase();
    strategy_list[kConfusion] = new MoveStrategyConfusion();
}

void GameLogic::CreateRoom(int id, int prev_room_id) {
    room_move_obj_.clear();
    room_static_obj_.clear();
    QFile room_file(QStringLiteral(":/Rooms/Data/Rooms/%1_room.txt").arg(id));
    curr_room_ = new Room(id, room_file);
    room_file.close();

    Pos player_spawn_pos;
    if (prev_room_id != -1) {
        player_spawn_pos = curr_room_->getEntrancePosByRoomId(prev_room_id);
    } else {
        player_spawn_pos = curr_room_->getEntrancesPos()[0];
    }

    LogInfo(LogMode::kConsole, 0,
            "Room created!\n|-->Width: " + std::to_string(curr_room_->getWidth()) +
            "\n|-->Height: " + std::to_string(curr_room_->getHeight()));

    QFile objects_file(QStringLiteral(":/RoomObjects/Data/RoomObjects/%1_objects.txt").arg(id));
    LoadCellObjects(objects_file, player_spawn_pos);
    objects_file.close();

    NotifyRoomChange();
    NotifyRoomObjectsChange();
    NotifyStaticObjectsChange();
}

void GameLogic::LoadRoom(Room* new_room, std::vector<PlaceableInCell*> new_room_move_obj,
                         std::vector<Furniture*> new_room_static_obj, int prev_room_id) {
    room_move_obj_.clear();
    room_static_obj_.clear();
    curr_room_ = new_room;
    room_move_obj_ = new_room_move_obj;
    room_static_obj_ = new_room_static_obj;
    AddPlayer(curr_room_->getEntrancePosByRoomId(prev_room_id));

    NotifyRoomChange();
    NotifyRoomObjectsChange();
    NotifyStaticObjectsChange();
}

Room& GameLogic::getRoom() {
    return *curr_room_;
}

std::vector<PlaceableInCell*>& GameLogic::getRoomMoveObjects() {
    return room_move_obj_;
}

std::vector<Furniture*>& GameLogic::getRoomStaticObjects() {
    return room_static_obj_;
}

void GameLogic::setRoomChangeObserver(RoomChangeObserver* new_obs) {
    room_change_obs_ = new_obs;
}

void GameLogic::NotifyRoomChanging(int id) {
    DeletePlayer();
    room_change_obs_->RoomChanging(id);
}

void GameLogic::NotifyObjectDestRules(PlaceableInCell* destroyed_obj) {
    room_change_obs_->RuleUpdate(destroyed_obj);
}

bool GameLogic::NotifyCheckRules(int next_room_id) {
    return room_change_obs_->RuleCheck(next_room_id);
}

void GameLogic::LoadCellObjects(QFile& obj_file, Pos player_spawn_pos) {
    if (obj_file.exists() && obj_file.open(QIODevice::ReadOnly)) {
        QString curr_line = obj_file.readLine();
        QStringList list_param;
        int num_objects = curr_line.toInt();

        int width_obj = 1;
        int height_obj = 1;

        // Отдельно создаем игрока в комнате
        AddPlayer(player_spawn_pos);

        LogInfo(LogMode::kConsole, 0,
                "Player added: \n|-->Position: (" + std::to_string(player_spawn_pos.x)
                + ", " + std::to_string(player_spawn_pos.y) + ")" +
                "\n|-->Sanity: " + std::to_string(Player::getInstance().getSanity()) +
                "\n|-->Damage to enemies: " + std::to_string(Player::getInstance().getDamageToEnemies()));

        for (int i=0; i < num_objects; i++) {
            curr_line = obj_file.readLine();
            list_param = curr_line.split(" ");
            switch(list_param[0].toInt()) {
            case(2):
                switch(list_param[1].toInt()) {
                case(1):
                    room_move_obj_.push_back(new Enemy(list_param[2].toInt(), Pos{list_param[3].toInt(), list_param[4].toInt()},
                                                 list_param[5].toInt(), list_param[6].toInt(), strategy_list[list_param[7].toInt()]));

                    LogInfo(LogMode::kConsole, 0,
                            "DamageableEnemy added: \n|-->Position: (" + std::to_string(list_param[3].toInt())
                            + ", " + std::to_string(list_param[4].toInt()) + ")" +
                            "\n|-->Image id: " + std::to_string(list_param[2].toInt()) +
                            "\n|-->Attack: " + std::to_string(list_param[5].toInt()) +
                            "\n|-->Life: " + std::to_string(list_param[6].toInt()));

                    break;
                case(2):
                    room_move_obj_.push_back(new LimitedLifeEnemy(list_param[2].toInt(), Pos{list_param[3].toInt(), list_param[4].toInt()},
                                                 list_param[5].toInt(), list_param[6].toInt(), strategy_list[list_param[7].toInt()]));

                    LogInfo(LogMode::kConsole, 0,
                            "LimitedLifeEnemy added: \n|-->Position: (" + std::to_string(list_param[3].toInt())
                            + ", " + std::to_string(list_param[4].toInt()) + ")" +
                            "\n|-->Image id: " + std::to_string(list_param[2].toInt()) +
                            "\n|-->Attack: " + std::to_string(list_param[5].toInt()) +
                            "\n|-->Life: " + std::to_string(list_param[6].toInt()));

                    break;
                case(3):
                    room_move_obj_.push_back(new ImmortalEnemy(list_param[2].toInt(), Pos{list_param[3].toInt(), list_param[4].toInt()},
                                                 list_param[5].toInt(), strategy_list[list_param[6].toInt()]));

                    LogInfo(LogMode::kConsole, 0,
                            "ImmortalEnemy added: \n|-->Position: (" + std::to_string(list_param[3].toInt())
                            + ", " + std::to_string(list_param[4].toInt()) + ")" +
                            "\n|-->Image id: " + std::to_string(list_param[2].toInt()) +
                            "\n|-->Attack: " + std::to_string(list_param[5].toInt()) +
                            "\n|-->Life: Inf");

                    break;
                }
                break;
            case(3):
                switch(list_param[1].toInt()) {
                case(1):
                    room_move_obj_.push_back(new SanityAffectItem(list_param[2].toInt(), Pos{list_param[3].toInt(),
                                                 list_param[4].toInt()}, list_param[5].toInt()));

                    LogInfo(LogMode::kConsole, 0,
                            "SanityAffectItem added: \n|-->Position: (" + std::to_string(list_param[3].toInt())
                            + ", " + std::to_string(list_param[4].toInt()) + ")" +
                            "\n|-->Image id: " + std::to_string(list_param[2].toInt()) +
                            "\n|-->Sanity heal: " + std::to_string(list_param[5].toInt()));

                    break;
                case(2):
                    room_move_obj_.push_back(new DamageToEnemiesItem(list_param[2].toInt(), Pos{list_param[3].toInt(),
                                                 list_param[4].toInt()}, list_param[5].toInt()));

                    LogInfo(LogMode::kConsole, 0,
                            "DamageToEnemiesItem added: \n|-->Position: (" + std::to_string(list_param[3].toInt())
                            + ", " + std::to_string(list_param[4].toInt()) + ")" +
                            "\n|-->Image id: " + std::to_string(list_param[2].toInt()) +
                            "\n|-->Damage up: " + std::to_string(list_param[5].toInt()));

                    break;
                case(3):
                    room_move_obj_.push_back(new KeyItem(list_param[2].toInt(), Pos{list_param[3].toInt(),
                                                 list_param[4].toInt()}));

                    LogInfo(LogMode::kConsole, 0,
                            "KeyItem added: \n|-->Position: (" + std::to_string(list_param[3].toInt())
                            + ", " + std::to_string(list_param[4].toInt()) + ")" +
                            "\n|-->Id: " + std::to_string(list_param[2].toInt()));

                    break;
                }
                break;
            case(4):
                room_static_obj_.push_back(new Furniture(list_param[1].toInt(), Pos{list_param[2].toInt(), list_param[3].toInt()},
                                               list_param[4].toInt(), list_param[5].toInt()));
                width_obj = list_param[4].toInt();
                height_obj = list_param[5].toInt();
                break;
            }

            Pos start_pos;
            if (list_param[0].toInt() != 4) {
                start_pos.x = list_param[3].toInt();
                start_pos.y = list_param[4].toInt();
                curr_room_->getRoomCell(start_pos.x, start_pos.y).setObject(room_move_obj_.back());
            } else {
                start_pos.x = list_param[2].toInt();
                start_pos.y = list_param[3].toInt();
                for (int y=0; y < height_obj; y++) {
                    for (int x=0; x < width_obj; x++) {
                        curr_room_->getRoomCell(start_pos.x + x, start_pos.y - y).setObject(room_static_obj_.back());
                    }
                }
            }
        }
    }
}

void GameLogic::MakeTurn(Pos player_pos_change) {
    Pos last_pos, curr_pos;
    for (int i=0; i < room_move_obj_.size(); i++) {
        last_pos = room_move_obj_[i]->getPos();
        if (room_move_obj_[i] == &Player::getInstance()) {
            room_move_obj_[i]->Move(Pos{last_pos.x + player_pos_change.x, last_pos.y + player_pos_change.y});
        } else {
            room_move_obj_[i]->Move();
        }
        curr_pos = room_move_obj_[i]->getPos();
        room_move_obj_[i]->setPos(last_pos);

        if (!(curr_pos == last_pos) && curr_pos.x < curr_room_->getWidth() && curr_pos.x >= 0 && \
                curr_pos.y < curr_room_->getHeight() && curr_pos.y >= 0) {
            if (curr_room_->getRoomCell(curr_pos).getObject() != nullptr) {
                PlaceableInCell* interact_obj = curr_room_->getRoomCell(curr_pos).getObject();
                room_move_obj_[i]->Interact(interact_obj);

                curr_room_->getRoomCell(room_move_obj_[i]->getPos()).setObject(room_move_obj_[i]);
                curr_room_->getRoomCell(interact_obj->getPos()).setObject(interact_obj);

                LogInfo(LogMode::kConsole, 0,
                        "Object interact another object, positions: (" + std::to_string(room_move_obj_[i]->getPos().x) +
                        ", " + std::to_string(room_move_obj_[i]->getPos().y) + ") <--> (" +
                        std::to_string(interact_obj->getPos().x) + ", " + std::to_string(interact_obj->getPos().y) + ")");
            } else {
                if (room_move_obj_[i] == &Player::getInstance()) {
                    if (curr_room_->getRoomCell(curr_pos).GetRoomId() != -1) {
                        if (NotifyCheckRules(curr_room_->getRoomCell(curr_pos).GetRoomId())) {
                            LogInfo(LogMode::kConsole, LogStyle::kNumbered,
                                    "Room changed to - " + std::to_string(curr_room_->getRoomCell(curr_pos).GetRoomId()));

                            NotifyRoomChanging(curr_room_->getRoomCell(curr_pos).GetRoomId());
                        }
                        break;
                    }
                    curr_room_->getRoomCell(curr_pos).Interact(Player::getInstance());
                    if (Player::getInstance().getPos() == curr_pos) {
                        room_move_obj_[i]->setPos(curr_pos);
                        curr_room_->getRoomCell(curr_pos).setObject(room_move_obj_[i]);
                        curr_room_->getRoomCell(last_pos).setObject(nullptr);
                    }
                } else {
                    if (typeid(curr_room_->getRoomCell(curr_pos)) != typeid(PathlessCell)) {
                        room_move_obj_[i]->setPos(curr_pos);
                        curr_room_->getRoomCell(curr_pos).setObject(room_move_obj_[i]);
                        curr_room_->getRoomCell(last_pos).setObject(nullptr);
                    }
                }
            }
        }
        if (room_move_obj_[i]->getLife() <= 0) {
            NotifyObjectDestroy(i);
            NotifyObjectDestRules(room_move_obj_[i]);
            curr_room_->getRoomCell(room_move_obj_[i]->getPos()).setObject(nullptr);
            delete room_move_obj_[i];
            room_move_obj_.erase(room_move_obj_.begin() + i);

            LogInfo(LogMode::kConsole, 0,
                    "Object destroyed at pos: (" + std::to_string(room_move_obj_[i]->getPos().x) +
                    ", " + std::to_string(room_move_obj_[i]->getPos().y) + ")");

        }
    }
    NotifyTurnComplete();
}

void GameLogic::DeletePlayer() {
    auto it = std::find(room_move_obj_.begin(), room_move_obj_.end(), &Player::getInstance());
    if (it != room_move_obj_.end())
        room_move_obj_.erase(it);
    curr_room_->getRoomCell(Player::getInstance().getPos()).setObject(nullptr);
}

void GameLogic::AddPlayer(Pos player_spawn_pos) {
    curr_room_->getRoomCell(player_spawn_pos).setObject(&Player::getInstance());
    Player::getInstance().Move(player_spawn_pos);
    room_move_obj_.insert(room_move_obj_.begin(), &Player::getInstance());
}

GameLogic::~GameLogic() {
    auto it = strategy_list.begin();
    while (it != strategy_list.end()) {
        delete it->second;
        it = strategy_list.erase(it);
    }
    DeleteAllObjects();
    delete curr_room_;

    delete &Logger::getInstance();
}

void GameLogic::DeleteAllObjects() {
    for (int i=0; i < room_move_obj_.size(); i++) {
        delete room_move_obj_[i];
    }
    for (int i=0; i < room_static_obj_.size(); i++) {
        delete room_static_obj_[i];
    }
    room_move_obj_.clear();
    room_static_obj_.clear();
}
