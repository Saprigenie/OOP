#ifndef TEMPLATERULE_H
#define TEMPLATERULE_H

#include "Rule.h"

template <int curr_room_id, int next_room_id>
class TemplateRule: public Rule {
public:
    TemplateRule() {};

    bool CheckRule(int check_curr_room, int check_next_room) {
        if (curr_room_id == check_curr_room && next_room_id == check_next_room) {
            return rule_done_;
        }
        return true;
    }
};

#endif // TEMPLATERULE_H
