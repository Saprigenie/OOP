#ifndef DESTROYOBJECTRULE_H
#define DESTROYOBJECTRULE_H

#include "TemplateRule.h"

template <int curr_room_id, int next_room_id, int obj_id>
class DestroyObjectRule: public TemplateRule<curr_room_id, next_room_id> {
public:
    DestroyObjectRule() {}

    void CheckRuleCondition(int check_curr_room, PlaceableInCell* check_obj) {
        if (!TemplateRule<curr_room_id, next_room_id>::rule_done_ && check_curr_room == curr_room_id) {
            if (check_obj->getId() == obj_id) {
                TemplateRule<curr_room_id, next_room_id>::rule_done_ = true;
            }

            TemplateRule<curr_room_id, next_room_id>::LogInfo(LogMode::kConsole, LogStyle::kTime,
            "(DestroyObjectRule) !is completed! passage between " + std::to_string(curr_room_id) + " and " +
             std::to_string(next_room_id) + " rooms now opened");
        }
    }
};

#endif // DESTROYOBJECTRULE_H
