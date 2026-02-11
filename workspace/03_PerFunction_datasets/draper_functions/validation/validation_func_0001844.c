SelectLevel(const CreatureInfo* cinfo, float percentHealth, float percentMana)
{
    uint32 rank = IsPet() ? 0 : cinfo->rank;


    uint32 minlevel = std::min(cinfo->maxlevel, cinfo->minlevel);
    uint32 maxlevel = std::max(cinfo->maxlevel, cinfo->minlevel);
    uint32 level = minlevel == maxlevel ? minlevel : urand(minlevel, maxlevel);
    SetLevel(level);

    float rellevel = maxlevel == minlevel ? 0 : (float(level - minlevel)) / (maxlevel - minlevel);


    float healthmod = _GetHealthMod(rank);

    uint32 minhealth = std::min(cinfo->maxhealth, cinfo->minhealth);
    uint32 maxhealth = std::max(cinfo->maxhealth, cinfo->minhealth);
    uint32 health = uint32(healthmod * (minhealth + uint32(rellevel * (maxhealth - minhealth))));

    SetCreateHealth(health);
    SetMaxHealth(health);

    if (percentHealth == 100.0f)
        SetHealth(health);
    else
        SetHealthPercent(percentHealth);


    uint32 minmana = std::min(cinfo->maxmana, cinfo->minmana);
    uint32 maxmana = std::max(cinfo->maxmana, cinfo->minmana);
    uint32 mana = minmana + uint32(rellevel * (maxmana - minmana));

    SetCreateMana(mana);
    SetMaxPower(POWER_MANA, mana);
    SetPower(POWER_MANA, mana);


    SetModifierValue(UNIT_MOD_HEALTH, BASE_VALUE, float(health));
    SetModifierValue(UNIT_MOD_MANA, BASE_VALUE, float(mana));


    float damagemod = _GetDamageMod(rank);

    SetBaseWeaponDamage(BASE_ATTACK, MINDAMAGE, cinfo->mindmg * damagemod);
    SetBaseWeaponDamage(BASE_ATTACK, MAXDAMAGE, cinfo->maxdmg * damagemod);

    SetBaseWeaponDamage(OFF_ATTACK, MINDAMAGE, cinfo->mindmg * damagemod);
    SetBaseWeaponDamage(OFF_ATTACK, MAXDAMAGE, cinfo->maxdmg * damagemod);

    SetFloatValue(UNIT_FIELD_MINRANGEDDAMAGE, cinfo->minrangedmg * damagemod);
    SetFloatValue(UNIT_FIELD_MAXRANGEDDAMAGE, cinfo->maxrangedmg * damagemod);

    SetModifierValue(UNIT_MOD_ATTACK_POWER, BASE_VALUE, cinfo->attackpower * damagemod);
}
