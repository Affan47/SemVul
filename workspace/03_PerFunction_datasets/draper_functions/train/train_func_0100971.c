UnloadMap(VMapManager2* vm)
    {
        for (loadedSpawnMap::iterator i = iLoadedSpawns.begin(); i != iLoadedSpawns.end(); ++i)
        {
            iTreeValues[i->first].setUnloaded();
            for (uint32 refCount = 0; refCount < i->second; ++refCount)
                { vm->releaseModelInstance(iTreeValues[i->first].name); }
        }
        iLoadedSpawns.clear();
        iLoadedTiles.clear();
    }
