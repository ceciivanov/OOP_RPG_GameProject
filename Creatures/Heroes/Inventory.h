
#ifndef GAMEPROJECT_INVENTORY_H
#define GAMEPROJECT_INVENTORY_H

#include "../../Items/Item.h"
#include "../../Items/Potion.h"
#include "../../Items/Armor.h"
#include "../../Items/Weapon.h"

#define INVENTORY_CAPACITY 20


class Inventory {

private:
    int addedItems = 0;

    Item** items = new Item*[INVENTORY_CAPACITY];

public:

    Inventory();

    ~Inventory();

    void print() const;

    bool empty() const;

    bool addItem(Item* newItem);
    Item * getItem(int pos);

    Item* changeItem(int pos, Item* item);
    void changeItem(Item* item1, Item* item2);

    Item* removeItem(int pos);
    void removeItem(Item* item);

    //methods for using some item from inventory, they are called by the hero
    Potion* choosePotion();
    Armor* chooseArmor();
    Weapon* chooseWeapon();

};


#endif //GAMEPROJECT_INVENTORY_H