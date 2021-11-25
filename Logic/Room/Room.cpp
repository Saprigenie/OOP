#include "Room.h"

Room::Room(int id, int exits_count, Pos* exits, int* items_to_exits, int width, int heigth): id_(id), room_width_(width), room_height_(heigth),
    entrance_count_(exits_count) {
    if (exits == nullptr || exits_count == 0) {
        throw std::logic_error("Сan not create a room without doors.");
    }
    entrances_pos_ = new Pos[entrance_count_];
    for (int i=0; i < entrance_count_; i++) {
        entrances_pos_[i].x = exits[i].x;
        entrances_pos_[i].y = exits[i].y;
        if (entrances_pos_[i].x >= 0 && entrances_pos_[i].x < room_width_ && \
                entrances_pos_[i].y >= 0 && entrances_pos_[i].y < room_height_) {
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
        entrance_count_ = curr_line.toInt();
        entrances_pos_ = new Pos[entrance_count_];
        int next_rooms_ind[entrance_count_];
        for (int i=0; i < entrance_count_; i++) {
            curr_line = room_file.readLine();
            next_rooms_ind[i] = curr_line.toInt();
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
                    room_cells_[x][y] = new EntranceCell(Pos{x, y}, next_rooms_ind[i]);
                    entrances_pos_[i] = Pos{x, y};
                    i++;
                    break;
                case(1):
                    room_cells_[x][y] = new PassableCell(Pos{x, y});
                    break;
                case(2):
                    room_cells_[x][y] = new ExitCell(Pos{x, y});
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
            room_cells_[x][y] = from.room_cells_[x][y];
        }
    }

    entrance_count_ = from.entrance_count_;
    entrances_pos_ = new Pos[entrance_count_];
    for (int i=0; i < entrance_count_; i++) {
        entrances_pos_[i].x = from.entrances_pos_[i].x;
        entrances_pos_[i].y = from.entrances_pos_[i].y;
    }
}

void Room::MoveRoom(Room &&from) {
    id_ = from.id_;
    entrance_count_ = from.entrance_count_;
    entrances_pos_ = from.entrances_pos_;

    room_width_ = from.room_width_;
    room_height_ = from.room_height_;
    room_cells_ = from.room_cells_;

    from.entrance_count_ = 0;
    from.entrances_pos_ = nullptr;
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

Pos* Room::getEntrancesPos() {
    return entrances_pos_;
}

Pos Room::getEntrancePosByRoomId(int id) {
    Pos res_pos = Pos{-1, -1};
    for (int i=0; i < entrance_count_; i++) {
        if (getRoomCell(entrances_pos_[i]).GetRoomId() == id) {
            res_pos = entrances_pos_[i];
        }
    }
    return res_pos;
}

void Room::ExitsCheck() {
    for (int i=0; i < entrance_count_; i++) {
        for (int j=i + 1; j < entrance_count_; j++) {
            if (abs(entrances_pos_[i].x - entrances_pos_[j].x) < 2 && abs(entrances_pos_[i].y - entrances_pos_[j].y) < 2) {
                throw std::logic_error("Exits can't be created side by side.");
            }
        }
    }
}

void Room::CreateCells(int* next_rooms_ind) {
    room_cells_ = new Cell**[room_width_];
    for (int x=0; x < room_width_; x++) {
        room_cells_[x] = new Cell*[room_height_];
        for (int y=0; y < room_height_; y++) {
            room_cells_[x][y] = new PassableCell(Pos{x, y});
        }
    }

    for (int i=0; i < entrance_count_; i++) {
        delete room_cells_[entrances_pos_[i].x][entrances_pos_[i].y];
        room_cells_[entrances_pos_[i].x][entrances_pos_[i].y] = new EntranceCell(Pos{entrances_pos_[i].x, entrances_pos_[i].y}, next_rooms_ind[i]);
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

    delete [] entrances_pos_;
}

Room::~Room() {
    ClearRoomCells();
}
