#include "Controller.h"

Controller::Controller(GameLogic* logic_, GameView* view): curr_logic_(logic_) {
    QObject::connect(view, SIGNAL(PlayerPressMove(Pos)), this, SLOT(PlayerChangePos(Pos)));
}

void Controller::PlayerChangePos(Pos player_pos_change) {
    curr_logic_->MakeTurn(player_pos_change);
}
