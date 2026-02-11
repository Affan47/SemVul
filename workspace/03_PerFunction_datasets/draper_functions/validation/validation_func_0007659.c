saveLodData(StreamSerialiser& stream, Terrain* terrain)
    {
        uint16 numLodLevels = terrain->getNumLodLevels();

        LodsData lods;
        separateData(terrain->mHeightData, terrain->getSize(), numLodLevels, lods);
        separateData(terrain->mDeltaData, terrain->getSize(), numLodLevels, lods);

        for (int level = numLodLevels - 1; level >=0; level--)
        {
            stream.writeChunkBegin(TERRAINLODDATA_CHUNK_ID, TERRAINLODDATA_CHUNK_VERSION);
            stream.startDeflate();
            stream.write(&(lods[level][0]), lods[level].size());
            stream.stopDeflate();
            stream.writeChunkEnd(TERRAINLODDATA_CHUNK_ID);
        }
    }
