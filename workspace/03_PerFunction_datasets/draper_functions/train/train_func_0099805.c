GetAreaFlag(float x, float y, float z, bool* isOutdoors) const
{
    uint32 mogpFlags;
    int32 adtId, rootId, groupId;
    WMOAreaTableEntry const* wmoEntry = 0;
    AreaTableEntry const* atEntry = 0;
    bool haveAreaInfo = false;

    if (GetAreaInfo(x, y, z, mogpFlags, adtId, rootId, groupId))
    {
        haveAreaInfo = true;
        wmoEntry = GetWMOAreaTableEntryByTripple(rootId, adtId, groupId);
        if (wmoEntry)
            { atEntry = GetAreaEntryByAreaID(wmoEntry->areaId); }
    }

    uint16 areaflag;
    if (atEntry)
        { areaflag = atEntry->exploreFlag; }
    else
    {
        if (GridMap* gmap = const_cast<TerrainInfo*>(this)->GetGrid(x, y))
            { areaflag = gmap->getArea(x, y); }

        else
            { areaflag = GetAreaFlagByMapId(GetMapId()); }
    }

    if (isOutdoors)
    {
        if (haveAreaInfo)
            { *isOutdoors = IsOutdoorWMO(mogpFlags); }
        else
            { *isOutdoors = true; }
    }
    return areaflag;
}
