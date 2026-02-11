setTerrainWorldSize(Real newWorldSize)
    {
        if (newWorldSize != mTerrainWorldSize)
        {
            mTerrainWorldSize = newWorldSize;
            for (TerrainSlotMap::iterator i = mTerrainSlots.begin(); i != mTerrainSlots.end(); ++i)
            {
                if (i->second->instance)
                {
                    i->second->instance->setWorldSize(newWorldSize);
                    i->second->instance->setPosition(getTerrainSlotPosition(i->second->x, i->second->y));
                }
            }
        }
    }
