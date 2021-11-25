#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <QObject>

#include "../../Game/ControllerObserver/ControllerObserver.h"
#include "../../Gui/GameView.h"

class Controller: public QObject {
private:
    Q_OBJECT
    ControllerObserver* obs_;
public:
    Controller(ControllerObserver* logic_, GameView* view);
public slots:
    void MoveArrowPushed(Pos player_pos_change);
};

#endif // CONTROLLER_H
