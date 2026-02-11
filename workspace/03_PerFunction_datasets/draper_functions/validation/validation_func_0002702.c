GetBoundInstance(uint32 mapid)
{
    MapEntry const* mapEntry = sMapStore.LookupEntry(mapid);
    if (!mapEntry)
        { return NULL; }

    BoundInstancesMap::iterator itr = m_boundInstances.find(mapid);
    if (itr != m_boundInstances.end())
        { return &itr->second; }
    else
        { return NULL; }
}
