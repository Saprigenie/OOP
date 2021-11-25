#ifndef MOVESTRATEGYCONFUSION_H
#define MOVESTRATEGYCONFUSION_H

#include <chrono>
#include <thread>

#include "MoveStrategy.h"
#include "../../Player/Player.h"
#include "../../../Room/Pos.h"

class MoveStrategyConfusion: public MoveStrategy {
public:
    virtual Pos Move(Pos curr_pos);
};

#endif // MOVESTRATEGYCONFUSION_H
