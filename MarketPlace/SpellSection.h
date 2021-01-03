#include <iostream>
#include "../Creatures/Heroes/Hero.h"


#ifndef GAMEPROJECT_SPELLSECTION_H
#define GAMEPROJECT_SPELLSECTION_H

#define SPELLS_CAPACITY 50

class SpellSection {

private:
    int addedSpells = 0;
    Spell** spells = new Spell*[SPELLS_CAPACITY];

public:

    ~SpellSection(){
        delete[] spells;
    }

    void buyOption(Hero* hero) {
        while(true)
        {
            std::cout << "Which spell you would like to buy ?" << std::endl;

            int pos;
            std::cin >> pos;

            if (pos == 0)
                return;

            pos--;

            Spell* spell = removeSpell(pos);

            if ( spell == nullptr )
            {
                std::cout << "Please choose available spell" << std::endl;
                continue;
            }

            hero->buySpell(spell);

            std::cout << "Available spells:" << std::endl;
            print();
            std::cout << "Your Acquired Skills" << std::endl;
            hero->printSkills();
        }
    }

    void sellOption(Hero* hero){
        while(true)
        {
            std::cout << "Which spell from yours you would like to sell ?" << std::endl;

            int pos;
            std::cin >> pos;

            if (pos == 0)
                break;

            pos--;

            Spell* spell = hero->sellSpell(pos);
            if ( spell == nullptr )
            {
                std::cout << "Please choose available spell" << std::endl;
                continue;
            }

            addSpell(spell);

            std::cout << "Available spells:" << std::endl;
            print();

            std::cout << "Your Acquired Skills" << std::endl;
            hero->printSkills();
        }
    }

    void open(Hero* hero){
        while(true)
        {
            std::cout << "Available spells:" << std::endl;
            print();

            std::cout << "Your Acquired Skills" << std::endl;
            hero->printSkills();

            std::cout << "0.Close Spells Section \t 1.Buy Spell \t 2.Sell Spell" << std::endl;

            int choice;
            std::cin >> choice;

            if (choice == 0)
            {
                std::cout << "Closing Spell Section" << std::endl;
                return;
            }
            else if (choice == 1)
            {
                buyOption(hero);
            }
            else if (choice == 2)
            {
                sellOption(hero);
            }
        }

    }

    void print() const{
        for (int i=0; i < SPELLS_CAPACITY; i++)
        {
            if (spells[i] != nullptr)
            {
                std::cout << i+1 << ")";
                spells[i]->print();
                std::cout << "Price: " << spells[i]->getPrice() << std::endl;
            }
        }
        std::cout << std::endl;
    }

    void addSpell(Spell* newSpell){
        if ( addedSpells >= SPELLS_CAPACITY )
            return;

        for(int i=0; i < SPELLS_CAPACITY; i++)
        {
            if ( spells[i] == nullptr )
            {
                spells[i] = newSpell;
                addedSpells++;
                return;
            }
        }
    }
    Spell* removeSpell(int pos){
        if (pos >= SPELLS_CAPACITY)
            return nullptr;

        Spell* temp = spells[pos];
        spells[pos] = nullptr;
        addedSpells--;

        return temp;
    }
};


#endif //GAMEPROJECT_SPELLSECTION_H