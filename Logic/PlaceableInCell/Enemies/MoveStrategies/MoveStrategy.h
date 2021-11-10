#ifndef MOVESTRATEGY_H
#define MOVESTRATEGY_H

#include <ctime>
#include <cstdlib>

#include "../../../Room/Pos.h"

class MoveStrategy {
public:
    virtual Pos Move(Pos curr_pos) = 0;
};

#endif // MOVESTRATEGY_H
