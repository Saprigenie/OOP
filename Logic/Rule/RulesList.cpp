#include "RulesList.h"

RulesList::RulesList() {}

void RulesList::AddRule(Rule* new_rule) {
    rules_.push_back(new_rule);
}

bool RulesList::CheckRules(int check_curr_room, int check_next_room) {
    for (Rule* p: rules_) {
        if (!p->CheckRule(check_curr_room, check_next_room)) {
            return false;
        }
    }
    return true;
}

void RulesList::CheckRulesCondition(int check_curr_room, PlaceableInCell* check_obj) {
    for (Rule* p: rules_)
        p->CheckRuleCondition(check_curr_room, check_obj);
}

RulesList::~RulesList() {
    for (Rule* p: rules_)
        delete p;
}
