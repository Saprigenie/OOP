#include "Controller.h"

Controller::Controller(ControllerObserver* new_obs_, GameView* view): obs_(new_obs_) {
    QObject::connect(view, SIGNAL(PlayerPressMove(Pos)), this, SLOT(MoveArrowPushed(Pos)));
}

void Controller::MoveArrowPushed(Pos player_pos_change) {
    obs_->PlayerChangePos(player_pos_change);
}
