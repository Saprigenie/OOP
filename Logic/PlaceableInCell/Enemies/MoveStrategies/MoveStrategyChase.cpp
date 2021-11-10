#include "MoveStrategyChase.h"

Pos MoveStrategyChase::Move(Pos curr_pos) {
    srand(time(NULL));
    int choise = rand() % 5;

    int player_x = Player::getInstance().getPos().x;
    int player_y = Player::getInstance().getPos().y;

    if (choise) {
        choise = rand() % 2;

        switch(choise) {
            case (0):
                curr_pos.x += (curr_pos.x < player_x) - (curr_pos.x > player_x);
                break;
            case (1):
                curr_pos.y += (curr_pos.y < player_y) - (curr_pos.y > player_y);
                break;
        }
    }
    return curr_pos;
}
