
#ifndef GAMEPROJECT_FIGHT_H
#define GAMEPROJECT_FIGHT_H

#include "../Squads/HeroSquad.h"
#include "../Squads/MonsterSquad.h"


class Fight {

private:

    HeroSquad* heroes = nullptr;
    MonsterSquad* enemies = nullptr;

    void displayStats() const;

    static void normalAttack(Hero* hero, Monster* monster);

    static void spellAttack(Hero* hero, Monster* monster);

    static void monsterAttack(Monster* monster, Hero* hero);


public:

    Fight(HeroSquad* heroes, MonsterSquad* enemies)
    :heroes(heroes), enemies(enemies){};

    ~Fight() = default;

    static bool begin();

    bool isNotOver() const;

    bool playerTurn();

    void enemiesTurn();

};


#endif //GAMEPROJECT_FIGHT_H