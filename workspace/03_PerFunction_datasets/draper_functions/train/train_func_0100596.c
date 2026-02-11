UnsummonMajordomoAdds()
    {
        for (GuidList::const_iterator itr = m_luiMajordomoAddsGUIDs.begin(); itr != m_luiMajordomoAddsGUIDs.end(); ++itr)
        {
            if (Creature* pAdd = m_creature->GetMap()->GetCreature(*itr))
                if (pAdd->IsTemporarySummon())
                {
                    ((TemporarySummon*)pAdd)->UnSummon();
                }
        }

        m_luiMajordomoAddsGUIDs.clear();
    }
