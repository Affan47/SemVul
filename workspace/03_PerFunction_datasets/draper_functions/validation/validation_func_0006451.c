IsOutdoors(float x, float y, float z) const
{
    uint32 mogpFlags;
    int32 adtId, rootId, groupId;


    if (!GetAreaInfo(x, y, z, mogpFlags, adtId, rootId, groupId))
        { return true; }

    return IsOutdoorWMO(mogpFlags);
}
