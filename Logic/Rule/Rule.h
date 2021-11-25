#ifndef RULE_H
#define RULE_H

#include "../PlaceableInCell/PlaceableInCell.h"
#include "../../Logging/Loggable/Loggable.h"

class Rule: public Loggable {
protected:
    bool rule_done_ = false;
public:
    virtual bool CheckRule(int check_curr_room, int check_next_room) = 0;
    virtual void CheckRuleCondition(int check_curr_room, PlaceableInCell* check_obj) = 0;
};

#endif // RULE_H
