#ifndef RULESLIST_H
#define RULESLIST_H

#include <vector>

#include "Rule.h"

class RulesList {
private:
    std::vector<Rule*> rules_;
public:
    RulesList();

    void AddRule(Rule* new_rule);

    bool CheckRules(int check_curr_room, int check_next_room);
    void CheckRulesCondition(int check_curr_room, PlaceableInCell* check_obj);

    ~RulesList();
};

#endif // RULESLIST_H
