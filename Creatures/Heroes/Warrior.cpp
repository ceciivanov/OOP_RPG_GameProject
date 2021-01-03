#include "Warrior.h"

void Warrior::print() const {
    std::cout << "Warrior: " << getName() << std::endl;
    std::cout << "Level: " << level << std::endl;
    std::cout << "Health: " << health << std::endl;
    std::cout << "Mana: " << mana << std::endl;
    std::cout << "Money: " << getMoney() << std::endl;
    std::cout << "Attributes: " << "\tStrength: " << strength << "\tDexterity: " << dexterity << "\tAgility:" << agility << std::endl;
}

void Warrior::levelUp() {
    level++;
    experience = START_XP;

    strength += INCREASE_WARRIOR_STRENGTH;
    dexterity += INCREASE_DEFAULT_DEXTERITY;
    agility += INCREASE_WARRIOR_AGILITY;
}
