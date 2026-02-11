InitWorldMaps()
{
    MapPersistentState* state = NULL;
    for (uint32 mapid = 0; mapid < sMapStore.GetNumRows(); ++mapid)
        if (MapEntry const* entry = sMapStore.LookupEntry(mapid))
            if (!entry->Instanceable())
                { state = AddPersistentState(entry, 0, 0, false, true, false); }

    if (state)
        { state->InitPools(); }
}
