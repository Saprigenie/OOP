#ifndef DESTROYEDOBJECTNUMRULE_H
#define DESTROYEDOBJECTNUMRULE_H

#include "TemplateRule.h"

template <int curr_room_id, int next_room_id, int num_obj>
class DestroyedObjectNumRule: public TemplateRule<curr_room_id, next_room_id> {
private:
    int destroyed_obj_num_;
public:
    DestroyedObjectNumRule() {
        destroyed_obj_num_ = 0;
    }

    void CheckRuleCondition(int check_curr_room, PlaceableInCell* check_obj) {
        if (!TemplateRule<curr_room_id, next_room_id>::rule_done_ && check_curr_room == curr_room_id) {
            destroyed_obj_num_ += 1;

            TemplateRule<curr_room_id, next_room_id>::LogInfo(LogMode::kConsole, LogStyle::kTime,
            "(DestroyedObjectNumRule) destroyed obj num now:" + std::to_string(destroyed_obj_num_) + ", need: " +
             std::to_string(num_obj));

            if (destroyed_obj_num_ >= num_obj) {
                TemplateRule<curr_room_id, next_room_id>::rule_done_ = true;

                TemplateRule<curr_room_id, next_room_id>::LogInfo(LogMode::kConsole, LogStyle::kTime,
                "(DestroyedObjectNumRule) !is completed! passage between " + std::to_string(curr_room_id) + " and " +
                 std::to_string(next_room_id) + " rooms now opened");
            }
        }
    }
};

#endif // DESTROYEDOBJECTNUMRULE_H
