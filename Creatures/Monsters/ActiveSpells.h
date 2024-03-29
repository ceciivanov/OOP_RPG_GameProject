
#ifndef GAMEPROJECT_ALLSPELLSDURATION_H
#define GAMEPROJECT_ALLSPELLSDURATION_H

#include "../../Spells/SpellEffect.h"

//this class keeps the information, for spells that are used on some monster, and must be changed depending on their duration

class ActiveSpells {

private:
    //types of spells effect
    SpellEffect fire;
    SpellEffect ice;
    SpellEffect lighting;

public:

    ActiveSpells()
    :fire(reduce_defence), ice(reduce_damage), lighting(reduce_dodge){}

    ~ActiveSpells() = default;

    void activate(EffectType type, int duration);

    void disable(EffectType type);

    void reduceDuration();

    bool expired(EffectType type);

};


#endif //GAMEPROJECT_ALLSPELLSDURATION_H