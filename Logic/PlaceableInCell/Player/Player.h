#ifndef PLAYER_H
#define PLAYER_H

#include <vector>
#include <algorithm>

#include "../PlaceableInCell.h"
#include "../Items/Item.h"
#include "../../Room/Pos.h"

class Player: public PlaceableInCell {
private:
    int sanity_;
    std::vector<int> player_items_;
    static Player* hero_obj;

    Player();
public:
    int damage_to_enemy_;

    static Player& getInstance();
    Player(const Player& from) = delete;
    Player& operator =(const Player& from) = delete;

    void setSanity(int sanity);
    int getSanity();
    int getNumItems();
    void Damage_sanity(int damage);
    void Heal_sanity(int heal);

    void appendItem(int id);
    void removeItem(int id);
    bool HasItem(int id);

    void Move(Pos new_pos = Pos{-1, -1});

    Interactions Interact(PlaceableInCell* to);
    Interactions Interact(Enemy& to);
    Interactions Interact(Item& to);
    Interactions Interact(Player& to);
};

#endif // PLAYER_H
