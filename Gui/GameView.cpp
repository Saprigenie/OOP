#include "GameView.h"
#include "ui_GameView.h"

GameView::GameView(GameLogic* new_logic, QWidget *parent) :
    QWidget(parent), ui(new Ui::GameView) {
    ui->setupUi(this);
    curr_logic_ = new_logic;
    curr_logic_->setObserver(this);

    room_scene = new QGraphicsScene(this);
    ui->room_view->setScene(room_scene);
    ui->room_view->scale(0.4, 0.4);
    ui->room_view->setFocusPolicy(Qt::NoFocus);
    ui->room_view->setRenderHint(QPainter::Antialiasing);
    ui->room_view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->room_view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    test_info = new QLabel(this);
    test_info->setGeometry(0, 0, 500, 700);
    test_info->setStyleSheet("QLabel {color: white;}");
}

void GameView::resizeEvent(QResizeEvent* event) {
    QWidget::resizeEvent(event);

    LogInfo(LogMode::kConsole, LogStyle::kNumbered,
            "Window resized");
}

void GameView::keyPressEvent(QKeyEvent* event) {
    // пока что жестко закреплены в коде, потом будут изменены
    if (event->key() == Qt::Key_Up) {
        emit PlayerPressMove(Pos{0, -1});
    } else if (event->key() == Qt::Key_Down) {
        emit PlayerPressMove(Pos{0, 1});
    } else if (event->key() == Qt::Key_Left) {
        emit PlayerPressMove(Pos{-1, 0});
    } else if (event->key() == Qt::Key_Right) {
        emit PlayerPressMove(Pos{1, 0});
    }
}

void GameView::UpdateRoomChange() {
    DeleteRoom();
    Room& curr_room = curr_logic_->getRoom();
    int width_room = curr_room.getWidth();
    int height_room = curr_room.getHeight();

    QPixmap floor_img(QStringLiteral(":/Img/Data/Img/Floor/%1_floor.jpg").arg(curr_room.getId()));
    QPixmap exit_img(QStringLiteral(":/Img/Data/Img/Floor/%1_exit.jpg").arg(curr_room.getId()));
    QPixmap entrance_img(QStringLiteral(":/Img/Data/Img/Floor/%1_entrance.jpg").arg(curr_room.getId()));

    floor_img = floor_img.scaled(floor_cell_size_, floor_cell_size_, Qt::KeepAspectRatio);
    exit_img = exit_img.scaled(floor_cell_size_, floor_cell_size_, Qt::KeepAspectRatio);
    entrance_img = entrance_img.scaled(floor_cell_size_, floor_cell_size_, Qt::KeepAspectRatio);

    for (int x = 0; x < width_room; x++) {
        for (int y = 0; y < height_room; y++) {
            QPixmap chosen_img;
            if (typeid(curr_room.getRoomCell(x, y)) == typeid(ExitCell)) {
                chosen_img = exit_img;
            } else if (typeid(curr_room.getRoomCell(x, y)) == typeid(EntranceCell)) {
                chosen_img = entrance_img;
            } else {
                chosen_img = floor_img;
            }
            QGraphicsPixmapItem* floor_item = room_scene->addPixmap(chosen_img);
            floor_item->setPos(x*floor_cell_size_, y*floor_cell_size_ + top_padding_scene_);
        }
    }
}

void GameView::UpdateRoomObjectsChange() {
    ClearObjects();
    auto room_obj = curr_logic_->getRoomObjects();
    for (int i=0; i < room_obj.size(); i++) {
        draw_objects_.push_back(new DrawableObject(room_scene, room_obj[i]->getId(), room_obj[i]->getPos(), floor_cell_size_, top_padding_scene_));
    }
    CenterViewOnPlayerPos();
}

void GameView::UpdateObjectDestroy(int i) {
    room_scene->removeItem(draw_objects_[i]);
    delete draw_objects_[i];
    draw_objects_.erase(draw_objects_.begin() + i);
}

void GameView::UpdateTurnComplete() {
    Room& curr_room = curr_logic_->getRoom();
    int width_room = curr_room.getWidth();
    int height_room = curr_room.getHeight();

    for (int x = 0; x < width_room; x++) {
        for (int y = 0; y < height_room; y++) {
            if (curr_room.getRoomCell(x, y).getObject()) {
                int i = std::find_if(curr_logic_->getRoomObjects().begin(), curr_logic_->getRoomObjects().end(),
                [x, y](PlaceableInCell* curr_obj) {
                    return curr_obj->getPos().x == x && curr_obj->getPos().y == y;
                }) - curr_logic_->getRoomObjects().begin();

                QPropertyAnimation* anim = new QPropertyAnimation(draw_objects_[i], "getScenePos");

                anim->setDuration(200);
                anim->setEndValue(draw_objects_[i]->RoomPosToScenePos(curr_logic_->getRoomObjects()[i]->getPos()));
                anim->start(QAbstractAnimation::DeleteWhenStopped);
            }
        }
    }
    CenterViewOnPlayerPos();
    TestShowPlayerConditions();
}

void GameView::UpdateWin() {
    QLabel* win = new QLabel("You win!");
    win->show();
}

void GameView::UpdateDefeat() {
    QLabel* defeat = new QLabel("You lose... your sanity ;)");
    defeat->show();
}

void GameView::TestShowPlayerConditions() {
    QString info = QStringLiteral("Player: "\
    "Sanity: %1\nDamage_to_enemies: %2\nNum_key_items: %3\n\n").arg(Player::getInstance().getSanity()
    ).arg(Player::getInstance().damage_to_enemy_).arg(Player::getInstance().getNumItems());

    test_info->setText(info);
}

void GameView::CenterViewOnPlayerPos() {
    Pos player_pos = Player::getInstance().getPos();
    ui->room_view->centerOn(floor_cell_size_* player_pos.x, floor_cell_size_* player_pos.y + floor_cell_size_);
}

void GameView::DeleteRoom() {
    ClearObjects();
    room_scene->clear();
}

void GameView::ClearObjects() {
    for (int i=0; i < draw_objects_.size(); i++) {
        room_scene->removeItem(draw_objects_[i]);
        delete draw_objects_[i];
    }

    draw_objects_.clear();
}

GameView::~GameView() {
    DeleteRoom();
    delete room_scene;
    delete ui;
}
