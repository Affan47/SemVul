HandleAuraConvertRune(bool apply, bool Real)
{
    if (!Real)
        return;

    if (GetTarget()->GetTypeId() != TYPEID_PLAYER)
        return;

    Player* plr = (Player*)GetTarget();

    if (plr->getClass() != CLASS_DEATH_KNIGHT)
        return;

    RuneType runeFrom = RuneType(GetSpellProto()->EffectMiscValue[m_effIndex]);
    RuneType runeTo   = RuneType(GetSpellProto()->EffectMiscValueB[m_effIndex]);

    if (apply)
    {
        for (uint32 i = 0; i < MAX_RUNES; ++i)
        {
            if (plr->GetCurrentRune(i) == runeFrom && !plr->GetRuneCooldown(i))
            {
                plr->ConvertRune(i, runeTo);
                break;
            }
        }
    }
    else
    {
        for (uint32 i = 0; i < MAX_RUNES; ++i)
        {
            if (plr->GetCurrentRune(i) == runeTo && plr->GetBaseRune(i) == runeFrom)
            {
                plr->ConvertRune(i, runeFrom);
                break;
            }
        }
    }
}
