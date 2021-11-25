#ifndef DRAWABLEOBJECT_H
#define DRAWABLEOBJECT_H

#include <QPixmap>
#include <QGraphicsScene>
#include <QGraphicsItem>
//#include <QRectF>
//#include <QObject>
#include <QPainter>

#include "../../Logic/Room/Pos.h"

class DrawableObject: public QObject, public QGraphicsItem {
private:
    Q_OBJECT
    Q_PROPERTY(QPointF getScenePos READ getScenePos WRITE setScenePos)
    int id_;
    Pos curr_pos_;
    int width_cell_;
    int top_padding_scene_;
    int height_;
    int width_;
    QPixmap obj_picture_;
public:
    DrawableObject(QGraphicsScene* scene, int id, Pos pos, int width_cell, int top_padding_scene,
                   int height = 1, int width = 1);

    Pos getRoomPos();
    void setRoomPos(Pos new_pos);
    QPointF getScenePos();
    void setScenePos(QPointF);
    QPointF RoomPosToScenePos(Pos new_pos);
    Pos ScenePosToRoomPos(QPointF new_pos);
    QPixmap getPixmap();
private:
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
};

#endif // DRAWABLEOBJECT_H
