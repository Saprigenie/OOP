#ifndef OBSERVER_H
#define OBSERVER_H

class Observer {
public:
    virtual void UpdateRoomChange() = 0;
    virtual void UpdateRoomObjectsChange() = 0;
    virtual void UpdateStaticObjectsChange() = 0;
    virtual void UpdateObjectDestroy(int i) = 0;
    virtual void UpdateTurnComplete() = 0;
    virtual void UpdateWin() = 0;
    virtual void UpdateDefeat() = 0;
};

#endif // OBSERVER_H
