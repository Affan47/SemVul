UpdateArmor()
{
    float value;
    UnitMods unitMod = UNIT_MOD_ARMOR;

    value  = GetModifierValue(unitMod, BASE_VALUE);
    value *= GetModifierValue(unitMod, BASE_PCT);
    value += GetStat(STAT_AGILITY) * 2.0f;
    value += GetModifierValue(unitMod, TOTAL_VALUE);


    AuraList const& mResbyIntellect = GetAurasByType(SPELL_AURA_MOD_RESISTANCE_OF_STAT_PERCENT);
    for (AuraList::const_iterator i = mResbyIntellect.begin(); i != mResbyIntellect.end(); ++i)
    {
        Modifier* mod = (*i)->GetModifier();
        if (mod->m_miscvalue & SPELL_SCHOOL_MASK_NORMAL)
            { value += int32(GetStat(STAT_INTELLECT) * mod->m_amount / 100.0f); }
    }

    value *= GetModifierValue(unitMod, TOTAL_PCT);

    SetArmor(int32(value));
}
