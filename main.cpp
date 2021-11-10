#include <QApplication>

#include "Gui/GameView.h"
#include "Logic/Room/Room.h"
#include "Logic/Room/Pos.h"
#include "Logic/GameLogic.h"
#include "Logic/Controller/Controller.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    GameLogic logic;
    logic.LogActive();
    GameView game_view(&logic);
    //game_view.LogActive();
    logic.CreateRoom();
    Controller control(&logic, &game_view);
    game_view.show();

    return a.exec();
}
