
#ifndef GAMEPROJECT_HERO_H
#define GAMEPROJECT_HERO_H

#include "../LivingCreature.h"

#include "Inventory.h"
#include "Skills.h"

#include "../../Items/Weapon.h"
#include "../../Items/Potion.h"
#include "../../Items/Armor.h"
#include "../../Spells/SpellEffect.h"


//use hero Type for player choice of hero
enum HeroType{warrior=1, paladin=2, sorcerer=3};


class Hero: public LivingCreature {

private:
    int CURRENT_HEALTH;
    int CURRENT_MANA;

    int money;

    Weapon* equippedWeapon = nullptr;
    Armor* equippedArmor = nullptr;

    Skills skills;
    Inventory inventory;

protected:
    int mana;
    int experience;
    int strength;
    int dexterity;
    int agility;

public:

    Hero(const std::string& name, int strength, int dexterity, int agility)
    :LivingCreature(name, START_LEVEL, START_HP), mana(START_MP), money(START_MONEY), experience(START_XP),
    strength(strength), dexterity(dexterity), agility(agility), CURRENT_HEALTH(START_HP), CURRENT_MANA(START_MP){}

    ~Hero() override = default;

    void print() const override = 0;

    virtual void levelUp() = 0;

    int getMoney() const;

    void printInventory() const;
    void printSkills() const;

    void reduceHealth(int reduce) override;

    bool dead() const;

    void earnMoney(int earned);
    void looseMoney();

    void addExperience(int xp);

    void setCurrentStats();

    bool avoidAttack() const;

    void regeneration() override;

    void revive();

    //transactions that are made by her in market
    void buyItem(Item* newItem);
    void buySpell(Spell* newSpell);

    Item* sellItem(int pos);
    Spell* sellSpell(int pos);

    //uses of items from inventory
    void equipWeapon(Weapon* weapon);
    void equipArmor(Armor* armor);
    void use(Potion* potion);

    //methods for the player

    int attack() const;

    void drinkPotion();

    //casting spell on monster, spell make some damage on monster and has an effect for some turns(duration)
    void castSpell(int& damage, int& effect, int& duration, EffectType& type);

    void checkInventory();


    void chooseEquipment() {
        Armor* arm = inventory.chooseArmor();

        if ( arm != nullptr )
        {
            if ( equippedArmor != nullptr ){
                inventory.changeItem(arm, equippedArmor);
            }
            else{
                inventory.removeItem(arm);
            }
            equipArmor(arm);
        }

        Weapon* weap = inventory.chooseWeapon();

        if ( weap != nullptr )
        {
            if ( equippedWeapon != nullptr ){
                inventory.changeItem(weap, equippedWeapon);
            }
            else{
                inventory.removeItem(weap);
            }
            equipWeapon(weap);
        }

    }

};


#endif //GAMEPROJECT_HERO_H