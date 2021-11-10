#include "MoveStrategyConfusion.h"

Pos MoveStrategyConfusion::Move(Pos curr_pos) {
    srand(time(NULL));
    int choise = rand() % 5;
    Pos new_pos;
    new_pos.x = Player::getInstance().getPos().x;
    new_pos.y = Player::getInstance().getPos().y;

    switch(choise) {
        case (0):
            new_pos.x += 1;
            break;
        case (1):
            new_pos.x -= 1;
            break;
        case (2):
            new_pos.y += 1;
            break;
        case (3):
            new_pos.y -= 1;
            break;
        case (4):
            new_pos = curr_pos;
            break;
    }
    return new_pos;
}
