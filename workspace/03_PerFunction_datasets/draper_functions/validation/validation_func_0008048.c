KilledUnit(Unit* victim)
{
    if (victim->GetTypeId() != TYPEID_PLAYER)
        { return; }

    for (CreatureEventAIList::iterator i = m_CreatureEventAIList.begin(); i != m_CreatureEventAIList.end(); ++i)
    {
        if ((*i).Event.event_type == EVENT_T_KILL)
            { ProcessEvent(*i, victim); }
    }
}
