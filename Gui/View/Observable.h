#ifndef OBSERVABLE_H
#define OBSERVABLE_H


#include "Observer.h"

class Observable {
    Observer* curr_obs_;
public:
    void setObserver(Observer* obs);

    void NotifyRoomChange();
    void NotifyRoomObjectsChange();
    void NotifyStaticObjectsChange();
    void NotifyObjectDestroy(int i);
    void NotifyTurnComplete();
    void NotifyWin();
    void NotifyDefeat();
};

#endif // OBSERVABLE_H
