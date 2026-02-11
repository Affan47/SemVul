ProcessForceFieldOpening()
{

    DoUseDoorOrButton(GO_FORCEFIELD);


    Creature* pImmolThar = GetSingleCreatureFromStorage(NPC_IMMOLTHAR);
    if (!pImmolThar || pImmolThar->IsDead())
    {
        return;
    }

    bool bHasYelled = false;
    for (GuidList::const_iterator itr = m_luiHighborneSummonerGUIDs.begin(); itr != m_luiHighborneSummonerGUIDs.end(); ++itr)
    {
        Creature* pSummoner = instance->GetCreature(*itr);

        if (!bHasYelled && pSummoner)
        {
            DoScriptText(SAY_KILL_IMMOLTHAR, pSummoner);
            bHasYelled = true;
        }

        if (!pSummoner || pSummoner->IsDead())
        {
            continue;
        }

        pSummoner->AI()->AttackStart(pImmolThar);
    }
    m_luiHighborneSummonerGUIDs.clear();
}
