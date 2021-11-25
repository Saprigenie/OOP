#ifndef CONTROLLEROBSERVER_H
#define CONTROLLEROBSERVER_H

#include "../../Logic/Room/Pos.h"

class ControllerObserver {
public:
    virtual void PlayerChangePos(Pos player_pos_change) = 0;
};

#endif // CONTROLLEROBSERVER_H
