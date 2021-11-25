#ifndef KEYITEMRULE_H
#define KEYITEMRULE_H

#include "TemplateRule.h"
#include "../PlaceableInCell/Player/Player.h"

template <int curr_room_id, int next_room_id, int item_id>
class KeyItemRule: public TemplateRule<curr_room_id, next_room_id> {
public:
    KeyItemRule() {}

    void CheckRuleCondition(int check_curr_room, PlaceableInCell* check_obj) {
        if (!TemplateRule<curr_room_id, next_room_id>::rule_done_) {
            if (Player::getInstance().HasItem(item_id)) {
                TemplateRule<curr_room_id, next_room_id>::rule_done_ = true;

                TemplateRule<curr_room_id, next_room_id>::LogInfo(LogMode::kConsole, LogStyle::kTime,
                "(KeyItemRule) !is completed! passage between " + std::to_string(curr_room_id) + " and " +
                 std::to_string(next_room_id) + " rooms now opened");
            }
        }
    }
};

#endif // KEYITEMRULE_H
