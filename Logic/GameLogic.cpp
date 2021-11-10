#include "GameLogic.h"

GameLogic::GameLogic() {
    strategy_list[kStandart] = new MoveStrategyStandart();
    strategy_list[kChase] = new MoveStrategyChase();
    strategy_list[kConfusion] = new MoveStrategyConfusion();
}

void GameLogic::CreateRoom(int id, int is_new_or_load) {
    // 0 - new; not 0 - load
    if (!is_new_or_load) {
        QFile room_file(QStringLiteral(":/Rooms/Data/Rooms/%1_room.txt").arg(id));
        curr_room_ = new Room(id, room_file);
        room_file.close();

        LogInfo(LogMode::kConsole, 0,
                "Room created!\n|-->Width: " + std::to_string(curr_room_->getWidth()) +
                "\n|-->Height: " + std::to_string(curr_room_->getHeight()));

        QFile objects_file(QStringLiteral(":/RoomObjects/Data/RoomObjects/%1_objects.txt").arg(id));
        LoadCellObjects(objects_file);
        objects_file.close();
    }
    NotifyRoomChange();
    NotifyRoomObjectsChange();
}

Room& GameLogic::getRoom() {
    return *curr_room_;
}

std::vector<PlaceableInCell*>& GameLogic::getRoomObjects() {
    return room_objects_;
}

void GameLogic::LoadCellObjects(QFile& obj_file) {
    if (obj_file.exists() && obj_file.open(QIODevice::ReadOnly)) {
        QString curr_line = obj_file.readLine();
        QStringList list_param;
        int num_objects = curr_line.toInt();
        PlaceableInCell* curr_obj;
        for (int i=0; i < num_objects; i++) {
            curr_line = obj_file.readLine();
            list_param = curr_line.split(" ");
            switch(list_param[0].toInt()) {
            case(1):
                curr_room_->getRoomCell(list_param[1].toInt(), list_param[2].toInt()).setObject(\
                        &Player::getInstance());
                Player::getInstance().Move(Pos{list_param[1].toInt(), list_param[2].toInt()});
                Player::getInstance().setSanity(list_param[3].toInt());
                Player::getInstance().damage_to_enemy_ = list_param[4].toInt();
                room_objects_.push_back(&Player::getInstance());

                LogInfo(LogMode::kConsole, 0,
                        "Player added: \n|-->Position: (" + std::to_string(list_param[1].toInt())
                        + ", " + std::to_string(list_param[2].toInt()) + ")" +
                        "\n|-->Sanity: " + std::to_string(list_param[3].toInt()) +
                        "\n|-->Damage to enemies: " + std::to_string(list_param[4].toInt()));

                break;
            case(2):
                switch(list_param[1].toInt()) {
                case(1):
                    curr_obj = new DamageableEnemy(list_param[2].toInt(), Pos{list_param[3].toInt(), list_param[4].toInt()},
                                list_param[5].toInt(), list_param[6].toInt(), strategy_list[(MoveStrategies)list_param[7].toInt()]);

                    LogInfo(LogMode::kConsole, 0,
                            "DamageableEnemy added: \n|-->Position: (" + std::to_string(list_param[3].toInt())
                            + ", " + std::to_string(list_param[4].toInt()) + ")" +
                            "\n|-->Image id: " + std::to_string(list_param[2].toInt()) +
                            "\n|-->Attack: " + std::to_string(list_param[5].toInt()) +
                            "\n|-->Life: " + std::to_string(list_param[6].toInt()));

                    break;
                case(2):
                    curr_obj = new LimitedLifeEnemy(list_param[2].toInt(), Pos{list_param[3].toInt(), list_param[4].toInt()},
                                list_param[5].toInt(), list_param[6].toInt(), strategy_list[(MoveStrategies)list_param[7].toInt()]);

                    LogInfo(LogMode::kConsole, 0,
                            "LimitedLifeEnemy added: \n|-->Position: (" + std::to_string(list_param[3].toInt())
                            + ", " + std::to_string(list_param[4].toInt()) + ")" +
                            "\n|-->Image id: " + std::to_string(list_param[2].toInt()) +
                            "\n|-->Attack: " + std::to_string(list_param[5].toInt()) +
                            "\n|-->Life: " + std::to_string(list_param[6].toInt()));

                    break;
                case(3):
                    curr_obj = new ImmortalEnemy(list_param[2].toInt(), Pos{list_param[3].toInt(), list_param[4].toInt()},
                                list_param[5].toInt(), strategy_list[(MoveStrategies)list_param[6].toInt()]);

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
                    curr_obj = new SanityAffectItem(list_param[2].toInt(), Pos{list_param[3].toInt(), list_param[4].toInt()},
                                list_param[5].toInt());

                    LogInfo(LogMode::kConsole, 0,
                            "SanityAffectItem added: \n|-->Position: (" + std::to_string(list_param[3].toInt())
                            + ", " + std::to_string(list_param[4].toInt()) + ")" +
                            "\n|-->Image id: " + std::to_string(list_param[2].toInt()) +
                            "\n|-->Sanity heal: " + std::to_string(list_param[5].toInt()));

                    break;
                case(2):
                    curr_obj = new DamageToEnemiesItem(list_param[2].toInt(), Pos{list_param[3].toInt(), list_param[4].toInt()},
                                list_param[5].toInt());

                    LogInfo(LogMode::kConsole, 0,
                            "DamageToEnemiesItem added: \n|-->Position: (" + std::to_string(list_param[3].toInt())
                            + ", " + std::to_string(list_param[4].toInt()) + ")" +
                            "\n|-->Image id: " + std::to_string(list_param[2].toInt()) +
                            "\n|-->Damage up: " + std::to_string(list_param[5].toInt()));

                    break;
                case(3):
                    curr_obj = new KeyItem(list_param[2].toInt(), Pos{list_param[3].toInt(), list_param[4].toInt()});

                    LogInfo(LogMode::kConsole, 0,
                            "KeyItem added: \n|-->Position: (" + std::to_string(list_param[3].toInt())
                            + ", " + std::to_string(list_param[4].toInt()) + ")" +
                            "\n|-->Id: " + std::to_string(list_param[2].toInt()));

                    break;
                }
                break;
            }
            if (list_param[0].toInt() != 1) {
                room_objects_.push_back(curr_obj);
                curr_room_->getRoomCell(list_param[3].toInt(), list_param[4].toInt()).setObject(curr_obj);
            }
        }
    }
}

void GameLogic::MakeTurn(Pos player_pos_change) {
    Pos last_pos, curr_pos;
    for (int i=0; i < room_objects_.size(); i++) {
        last_pos = room_objects_[i]->getPos();
        if (room_objects_[i] == &Player::getInstance()) {
            room_objects_[i]->Move(Pos{last_pos.x + player_pos_change.x, last_pos.y + player_pos_change.y});
        } else {
            room_objects_[i]->Move();
        }
        curr_pos = room_objects_[i]->getPos();
        room_objects_[i]->setPos(last_pos);

        if (curr_pos.x == last_pos.x && curr_pos.y == last_pos.y) {
            continue;
        }

        if (curr_pos.x < curr_room_->getWidth() && curr_pos.x >= 0 && \
                curr_pos.y < curr_room_->getHeight() && curr_pos.y >= 0) {
            if (curr_room_->getRoomCell(curr_pos).getObject() != nullptr) {
                PlaceableInCell* interact_obj = curr_room_->getRoomCell(curr_pos).getObject();
                Interactions interaction = room_objects_[i]->Interact(interact_obj);

                curr_room_->getRoomCell(room_objects_[i]->getPos()).setObject(room_objects_[i]);
                curr_room_->getRoomCell(interact_obj->getPos()).setObject(interact_obj);

                if (interaction == kI_interact_P) {
                    curr_room_->getRoomCell(last_pos).setObject(nullptr);
                    delete room_objects_[i];
                    room_objects_.erase(room_objects_.begin() + i);
                    NotifyObjectDestroy(i);

                    LogInfo(LogMode::kConsole, LogStyle::kTime,
                            "Player interact with item at position: (" + std::to_string(last_pos.x) +
                            ", " + std::to_string(last_pos.y) + ")");

                } else if (interaction == kP_interact_I) {
                    auto interact_obj_pos = std::find(room_objects_.begin(), room_objects_.end(), interact_obj);
                    curr_room_->getRoomCell(last_pos).setObject(nullptr);
                    curr_room_->getRoomCell(room_objects_[i]->getPos()).setObject(room_objects_[i]);
                    delete interact_obj;
                    room_objects_.erase(interact_obj_pos);
                    NotifyObjectDestroy(interact_obj_pos - room_objects_.begin());

                    LogInfo(LogMode::kConsole, 0,
                            "Player interact with item at position: (" + std::to_string(room_objects_[i]->getPos().x) +
                            ", " + std::to_string(room_objects_[i]->getPos().y) + ")");

                } else {

                    LogInfo(LogMode::kConsole, 0,
                            "Object interact another object, positions: (" + std::to_string(room_objects_[i]->getPos().x) +
                            ", " + std::to_string(room_objects_[i]->getPos().y) + ") <--> (" +
                            std::to_string(interact_obj->getPos().x) + ", " + std::to_string(interact_obj->getPos().y) + ")");

                }
            } else {
                if (room_objects_[i] == &Player::getInstance()) {
                    bool end = curr_room_->getRoomCell(curr_pos).PlayerInteract(Player::getInstance());
                    if (Player::getInstance().getPos() == curr_pos) {
                        room_objects_[i]->setPos(curr_pos);
                        curr_room_->getRoomCell(curr_pos).setObject(room_objects_[i]);
                        curr_room_->getRoomCell(last_pos).setObject(nullptr);
                    }
                    if (end) {
                        NotifyWin();
                    }
                } else {
                    room_objects_[i]->setPos(curr_pos);
                    curr_room_->getRoomCell(curr_pos).setObject(room_objects_[i]);
                    curr_room_->getRoomCell(last_pos).setObject(nullptr);
                }
            }
        }
    }
    NotifyTurnComplete();
}

GameLogic::~GameLogic() {
    auto it = strategy_list.begin();
    while (it != strategy_list.end()) {
        delete it->second;
        it = strategy_list.erase(it);
    }
    delete curr_room_;

    delete &Logger::getInstance();
}
