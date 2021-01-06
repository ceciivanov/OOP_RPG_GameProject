
#ifndef GAMEPROJECT_MONSTER_H
#define GAMEPROJECT_MONSTER_H

#include "MONSTER_ATTRIBUTES.h"
#include "../LivingCreature.h"
#include "../../Range.h"
#include "../Heroes/Hero.h"
#include "../../Spells/AllSpellsEffect.h"

enum MonsterType{dragon=1, exoskeleton=2, spirit=3};


class Monster: public LivingCreature {

private:
    const int INIT_DODGE;
    const int INIT_DEFENCE;
    const Range INIT_DAMAGE;

protected:
    Range damageRange;
    int defence;
    int dodge;
    AllSpellsEffect allspellsduration;
public:

    Monster(const std::string& name, int level, Range range, int defence, int dodge)
    :LivingCreature(name, level, START_HP), damageRange(range), defence(defence), dodge(dodge), INIT_DODGE(dodge), INIT_DEFENCE(defence), INIT_DAMAGE(range){};

    ~Monster() override = default;

    void print() const override = 0;

    virtual int attack() const = 0;

    int getDefence() const;

    void reduceDamage(int reduce);
    void reduceDefence(int reduce);
    void reduceDodge(int reduce);

    void regeneration() override;

    bool avoidAttack() const;

    
    void activateSpell(EffectType type, int duration){
        allspellsduration.activate(type, duration);
    }

    bool disableSpells(EffectType type){
        return allspellsduration.disable(type);
    }

    void reduceSpellsRound(){
        allspellsduration.reduceRound();
    }

    bool mustDisable(EffectType type){
        return allspellsduration.mustDisable(type);
    }


};


#endif //GAMEPROJECT_MONSTER_H