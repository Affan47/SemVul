CheckPower()
{

    if (m_CastItem)
        { return SPELL_CAST_OK; }


    if (m_caster->GetTypeId() != TYPEID_PLAYER && m_caster->HasFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_QUESTGIVER) != m_caster->IsInCombat())
        { return SPELL_CAST_OK; }


    if (m_spellInfo->powerType == POWER_HEALTH)
    {
        if (m_caster->GetHealth() <= m_powerCost)
            { return SPELL_FAILED_CANT_DO_THAT_YET; }
        return SPELL_CAST_OK;
    }


    if (m_spellInfo->powerType >= MAX_POWERS)
    {
        sLog.outError("Spell::CheckMana: Unknown power type '%d'", m_spellInfo->powerType);
        return SPELL_FAILED_UNKNOWN;
    }


    Powers powerType = Powers(m_spellInfo->powerType);
    if (m_caster->GetPower(powerType) < m_powerCost)
        { return SPELL_FAILED_NO_POWER; }

    return SPELL_CAST_OK;
}
