#ifndef MOVESTRATEGYSTANDART_H
#define MOVESTRATEGYSTANDART_H

#include "MoveStrategy.h"
#include "../../../Room/Pos.h"

class MoveStrategyStandart: public MoveStrategy {
public:
    virtual Pos Move(Pos curr_pos);
};

#endif // MOVESTRATEGYSTANDART_H
