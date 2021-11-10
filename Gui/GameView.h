#ifndef GAMEVIEW_H
#define GAMEVIEW_H

#include <vector>
#include <typeinfo>

#include <QSizePolicy>
#include <QResizeEvent>
#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include <QPropertyAnimation>
#include <QLabel>
#include <QWidget>

#include "View/Observer.h"
#include "../Logging/Loggable/Loggable.h"
#include "../Logic/GameLogic.h"
#include "DrawObject/DrawableObject.h"

namespace Ui {
class GameView;
}

class GameView : public QWidget, public Observer, public Loggable {
private:
    Q_OBJECT

    Ui::GameView *ui;
    QGraphicsScene* room_scene;
    GameLogic* curr_logic_;
    std::vector<DrawableObject*> draw_objects_;

    int floor_cell_size_ = 500;
    int top_padding_scene_ = 500;

    virtual void resizeEvent(QResizeEvent* event);
    virtual void keyPressEvent(QKeyEvent *event);

    QLabel* test_info;
public:
    explicit GameView(GameLogic* new_logic, QWidget *parent = nullptr);

    void UpdateRoomChange();
    void UpdateRoomObjectsChange();
    void UpdateObjectDestroy(int i);
    void UpdateTurnComplete();
    void UpdateWin();
    void UpdateDefeat();

    void TestShowPlayerConditions();
    void CenterViewOnPlayerPos();

    void ClearObjects();
    void DeleteRoom();

    ~GameView();
signals:
    void PlayerPressMove(Pos);
};

#endif // GAMEVIEW_H
