#include "Room.h"

Room::Room(int id, int exits_count, Pos* exits, int* items_to_exits, int width, int heigth): id_(id), room_width_(width), room_height_(heigth),
    exits_count_(exits_count) {
    if (exits == nullptr || exits_count == 0) {
        throw std::logic_error("Сan not create a room without doors.");
    }
    exits_pos_ = new Pos[exits_count_];
    for (int i=0; i < exits_count_; i++) {
        exits_pos_[i].x = exits[i].x;
        exits_pos_[i].y = exits[i].y;
        if (exits_pos_[i].x >= 0 && exits_pos_[i].x < room_width_ && \
                exits_pos_[i].y >= 0 && exits_pos_[i].y < room_height_) {
        } else {
            throw std::out_of_range("Exits outside the room.");
        }
    }
    CreateCells(items_to_exits);
    ExitsCheck();
}

Room::Room(int id, QFile& room_file): id_(id) {
    if (room_file.exists() && room_file.open(QIODevice::ReadOnly)) {
        QString curr_line = room_file.readLine();
        QStringList cell_list = curr_line.split(" ");
        room_width_ = cell_list[0].toInt();
        room_height_ = cell_list[1].toInt();

        curr_line = room_file.readLine();
        exits_count_ = curr_line.toInt();
        exits_pos_ = new Pos[exits_count_];
        int exits_item_ind[exits_count_];
        for (int i=0; i < exits_count_; i++) {
            curr_line = room_file.readLine();
            exits_item_ind[i] = curr_line.toInt();
        }
        int i=0;

        room_cells_ = new Cell**[room_width_];
        for (int x=0; x < room_width_; x++) {
            room_cells_[x] = new Cell*[room_height_];
        }

        for (int y = 0; y < room_height_; y++) {
            curr_line = room_file.readLine();
            cell_list = curr_line.split(" ");
            for (int x = 0; x < room_width_; x++) {
                switch(cell_list[x].toInt()) {
                case(0):
                    room_cells_[x][y] = new EntranceCell(Pos{x, y});
                    break;
                case(1):
                    room_cells_[x][y] = new PassableCell(Pos{x, y});
                    break;
                case(2):
                    room_cells_[x][y] = new ExitCell(Pos{x, y}, exits_item_ind[i]);
                    exits_pos_[i] = Pos{x, y};
                    i++;
                    break;
                case(3):
                    room_cells_[x][y] = new PathlessCell(Pos{x, y});
                    break;
                }
            }
        }
        ExitsCheck();
    }
}

Room::Room(const Room& from) {
    CopyRoom(from);
}

Room& Room::operator =(const Room& from) {
    if (&from != this) {
        ClearRoomCells();
        CopyRoom(from);
    }
    return *this;
}

Room::Room(Room&& from) {
    MoveRoom(std::move(from));
}

Room& Room::operator =(Room&& from) {
    if (&from != this) {
        MoveRoom(std::move(from));
    }
    return *this;
}

void Room::CopyRoom(const Room& from) {
    id_ = from.id_;
    room_width_ = from.room_width_;
    room_height_ = from.room_height_;
    room_cells_ = new Cell**[room_width_];
    for (int x=0; x < room_width_; x++) {
        room_cells_[x] = new Cell*[room_height_];
        for (int y=0; y < room_height_; y++) {
            // ????
            room_cells_[x][y] = from.room_cells_[x][y];
        }
    }

    exits_count_ = from.exits_count_;
    exits_pos_ = new Pos[exits_count_];
    for (int i=0; i < exits_count_; i++) {
        exits_pos_[i].x = from.exits_pos_[i].x;
        exits_pos_[i].y = from.exits_pos_[i].y;
    }
}

void Room::MoveRoom(Room &&from) {
    id_ = from.id_;
    exits_count_ = from.exits_count_;
    exits_pos_ = from.exits_pos_;

    room_width_ = from.room_width_;
    room_height_ = from.room_height_;
    room_cells_ = from.room_cells_;

    from.exits_count_ = 0;
    from.exits_pos_ = nullptr;
    from.room_width_ = 0;
    from.room_height_ = 0;
    from.room_cells_ = nullptr;
}

int Room::getId() {
    return id_;
}

int Room::getWidth() {
    return room_width_;
}
int Room::getHeight() {
    return room_height_;
}

Cell& Room::getRoomCell(int x, int y) {
    return *room_cells_[x][y];
}

Cell& Room::getRoomCell(Pos cell_pos) {
    return *room_cells_[cell_pos.x][cell_pos.y];
}

void Room::ExitsCheck() {
    for (int i=0; i < exits_count_; i++) {
        if (exits_pos_[i].x != room_width_-1 && exits_pos_[i].y != room_height_-1 \
                              && exits_pos_[i].x != 0 && exits_pos_[i].y != 0) {
            throw std::logic_error("Exits can only be created along the walls of the room.");
        }
        for (int j=i + 1; j < exits_count_; j++) {
            if (abs(exits_pos_[i].x - exits_pos_[j].x) < 2 && abs(exits_pos_[i].y - exits_pos_[j].y) < 2) {
                throw std::logic_error("Exits can't be created side by side.");
            }
        }
    }
}

void Room::CreateCells(int* items_to_exits) {
    room_cells_ = new Cell**[room_width_];
    for (int x=0; x < room_width_; x++) {
        room_cells_[x] = new Cell*[room_height_];
        for (int y=0; y < room_height_; y++) {
            room_cells_[x][y] = new PassableCell(Pos{x, y});
        }
    }

    for (int i=0; i < exits_count_; i++) {
        delete room_cells_[exits_pos_[i].x][exits_pos_[i].y];
        room_cells_[exits_pos_[i].x][exits_pos_[i].y] = new ExitCell(Pos{exits_pos_[i].x, exits_pos_[i].y}, items_to_exits[i]);
    }
}

void Room::ClearRoomCells() {
    for (int x=0; x < room_width_; x++) {
        for (int y=0; y < room_height_; y++) {
            delete room_cells_[x][y];
        }
        delete [] room_cells_[x];
    }
    delete [] room_cells_;

    delete [] exits_pos_;
}

Room::~Room() {
    ClearRoomCells();
}
