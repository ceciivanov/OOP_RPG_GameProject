#include "MonsterSquad.h"


void MonsterSquad::print() const {
    for (int i=0; i < numberOfMonsters; i++){
        monsters[i]->print();
    }
}


int MonsterSquad::getSize() const {
    return numberOfMonsters;
}


Monster *MonsterSquad::getMonster(int pos) const {
    if (pos >= numberOfMonsters )
        return nullptr;

    return monsters[pos];
}


void MonsterSquad::setMonster(Monster *monster) {
    for(int i=0; i < numberOfMonsters; i++)
    {
        if (monsters[i] == nullptr )
        {
            monsters[i] = monster;
            return;
        }
    }
}


bool MonsterSquad::defeated() const {
    int totalHealth=0;
    for(int i=0; i < numberOfMonsters; i++){
        totalHealth += monsters[i]->getHealth();
    }

    return (totalHealth==0);
}


void MonsterSquad::regeneration() {
    for(int i=0; i < numberOfMonsters; i++){
        monsters[i]->regeneration();
    }
}