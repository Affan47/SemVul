getTerrainDefinition(long x, long y) const
    {
        TerrainSlot* slot = getTerrainSlot(x, y);
        if (slot)
            return &slot->def;
        else
            return 0;

    }
