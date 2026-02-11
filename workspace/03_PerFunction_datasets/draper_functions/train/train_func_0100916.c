LoadEventScripts()
{
    LoadScripts(sEventScripts, "dbscripts_on_event");

    std::set<uint32> eventIds;
    CollectPossibleEventIds(eventIds);


    for (ScriptMapMap::const_iterator itr = sEventScripts.second.begin(); itr != sEventScripts.second.end(); ++itr)
    {
        std::set<uint32>::const_iterator itr2 = eventIds.find(itr->first);
        if (itr2 == eventIds.end())
            sLog.outErrorDb("Table `dbscripts_on_event` has script (Id: %u) not referring to any fitting gameobject_template or any spell effect %u or path taxi node data",
                            itr->first, SPELL_EFFECT_SEND_EVENT);
    }
}
