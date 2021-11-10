#ifndef MOVESTRATEGYCHASE_H
#define MOVESTRATEGYCHASE_H

#include "MoveStrategy.h"
#include "../../Player/Player.h"
#include "../../../Room/Pos.h"

class MoveStrategyChase: public MoveStrategy {
public:
    virtual Pos Move(Pos curr_pos);
};

#endif // MOVESTRATEGYCHASE_H
