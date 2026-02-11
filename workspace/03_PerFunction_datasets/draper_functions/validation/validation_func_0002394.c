canMergeWithRegion(const rcRegion& rega, const rcRegion& regb)
{
    if (rega.areaType != regb.areaType)
        return false;
    int n = 0;
    for (int i = 0; i < rega.connections.size(); ++i)
    {
        if (rega.connections[i] == regb.id)
            n++;
    }
    if (n > 1)
        return false;
    for (int i = 0; i < rega.floors.size(); ++i)
    {
        if (rega.floors[i] == regb.id)
            return false;
    }
    return true;
}
