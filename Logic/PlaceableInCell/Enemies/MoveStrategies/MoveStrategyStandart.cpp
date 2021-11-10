#include "MoveStrategyStandart.h"

Pos MoveStrategyStandart::Move(Pos curr_pos) {
    srand(time(NULL));
    int choise = rand() % 4;
    switch(choise) {
        case (0):
            curr_pos.x += 1;
            break;
        case (1):
            curr_pos.x -= 1;
            break;
        case (2):
            curr_pos.y += 1;
            break;
        case (3):
            curr_pos.y -= 1;
            break;
    }
    return curr_pos;
}
