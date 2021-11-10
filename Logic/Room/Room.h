#ifndef ROOM_H
#define ROOM_H

#include <stdexcept>

#include <QFile>

#include "../Cell/Cell.h"
#include "../Cell/CellTypes/EntranceCell.h"
#include "../Cell/CellTypes/PassableCell.h"
#include "../Cell/CellTypes/ExitCell.h"
#include "../Cell/CellTypes/PathlessCell.h"
#include "Pos.h"

class Room {
private:
    int id_;

    Cell*** room_cells_;
    int room_width_;
    int room_height_;

    Pos* exits_pos_;
    int exits_count_;

    void ClearRoomCells();
    void CopyRoom(const Room& from);
    void MoveRoom(Room&& from);
    void CreateCells(int* items_to_exits);
    void ExitsCheck();

public:
    Room(int id, int exits_count, Pos* exits, int* items_to_exits, int width = 10, int heigth = 10);
    Room(int id, QFile& room_file);
    Room(const Room& from);
    Room& operator =(const Room& from);
    Room(Room&& from);
    Room& operator =(Room&& from);

    int getId();
    int getWidth();
    int getHeight();
    Cell& getRoomCell(int x, int y);
    Cell& getRoomCell(Pos cell_pos);

    ~Room();
};

#endif // ROOM_H
