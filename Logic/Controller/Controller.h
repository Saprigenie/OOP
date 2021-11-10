#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <QObject>

#include "../GameLogic.h"
#include "../../Gui/GameView.h"

class Controller: public QObject {
private:
    Q_OBJECT
    GameLogic* curr_logic_;
public:
    Controller(GameLogic* logic_, GameView* view);
public slots:
    void PlayerChangePos(Pos player_pos_change);
};

#endif // CONTROLLER_H
