#include "Dragon.h"

int Dragon::attack() const {
    return damageRange.getValue();
}

void Dragon::print() const {
    std::cout << "Dragon " << getName() << std::endl;
    std::cout << "Level " << level << std::endl;
    std::cout << "Health " << getHealth() << std::endl;
    std::cout << "Damage range: ";
    damageRange.print();
    std::cout << "Defence " << defence << " Dodge " << dodge << std::endl;
}
