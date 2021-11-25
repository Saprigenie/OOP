#include "DrawableObject.h"

DrawableObject::DrawableObject(QGraphicsScene* scene, int id, Pos pos, int width_cell, int top_padding_scene,
                               int height, int width) {
    id_ = id;
    curr_pos_ = pos;
    height_ = height;
    width_ = height;
    width_cell_ = width_cell;
    top_padding_scene_ = top_padding_scene;
    obj_picture_.load(QStringLiteral(":/Img/Data/Img/Objects/%1_obj.png").arg(id_));

    double height_fact = ((double)obj_picture_.height())/obj_picture_.width();
    obj_picture_ = obj_picture_.scaled(width_cell_*width_, width_cell_*width_*height_fact);
    this->setPos(curr_pos_.x * width_cell_, top_padding_scene_ + curr_pos_.y * width_cell_ + width_cell_ - height_fact * width_ * width_cell_);
    this->setZValue(curr_pos_.y);
    scene->addItem(this);
}

Pos DrawableObject::getRoomPos() {
    return curr_pos_;
}

void DrawableObject::setRoomPos(Pos new_pos) {
    curr_pos_ = new_pos;
    this->setZValue(curr_pos_.y);
    this->setPos(RoomPosToScenePos(curr_pos_));
}

QPointF DrawableObject::getScenePos() {
    return this->pos();
}

void DrawableObject::setScenePos(QPointF new_pos) {
    curr_pos_ = ScenePosToRoomPos(new_pos);
    this->setZValue(curr_pos_.y);
    this->setPos(new_pos);
}

QPointF DrawableObject::RoomPosToScenePos(Pos new_pos) {
    return QPoint{new_pos.x * width_cell_, top_padding_scene_ + new_pos.y*width_cell_ + width_cell_ - obj_picture_.height()};
}

Pos DrawableObject::ScenePosToRoomPos(QPointF new_pos) {
    return Pos{int(new_pos.x())/width_cell_, (-top_padding_scene_ + int(new_pos.y()) - width_cell_ + obj_picture_.height())/width_cell_};
}

QPixmap DrawableObject::getPixmap() {
    return obj_picture_;
}

QRectF DrawableObject::boundingRect() const {
    return QRectF(0, 0, obj_picture_.width(), obj_picture_.height());
}

void DrawableObject::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    painter->drawPixmap(0,0, obj_picture_);
}
