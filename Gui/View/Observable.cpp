#include "Observable.h"

void Observable::setObserver(Observer* obs){
    curr_obs_ = obs;
}

void Observable::NotifyRoomChange() {
    curr_obs_->UpdateRoomChange();
}

void Observable::NotifyRoomObjectsChange() {
    curr_obs_->UpdateRoomObjectsChange();
}

void Observable::NotifyObjectDestroy(int i) {
    curr_obs_->UpdateObjectDestroy(i);
}

void Observable::NotifyTurnComplete() {
    curr_obs_->UpdateTurnComplete();
}

void Observable::NotifyWin() {
    curr_obs_->UpdateWin();
}

void Observable::NotifyDefeat() {
    curr_obs_->UpdateDefeat();
}

