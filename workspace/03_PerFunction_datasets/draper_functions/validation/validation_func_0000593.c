ExistMap(uint32 mapid, int gx, int gy)
{
    int len = sWorld.GetDataPath().length() + strlen("maps/%03u%02u%02u.map") + 1;
    char* tmp = new char[len];
    snprintf(tmp, len, (char*)(sWorld.GetDataPath() + "maps/%03u%02u%02u.map").c_str(), mapid, gx, gy);

    FILE* pf = fopen(tmp, "rb");

    if (!pf)
    {
        sLog.outError("Check existing of map file '%s': not exist!", tmp);
        delete[] tmp;
        return false;
    }

    GridMapFileHeader header;
    fread(&header, sizeof(header), 1, pf);
    if (header.mapMagic     != *((uint32 const*)(MAP_MAGIC)) ||
            header.versionMagic != *((uint32 const*)(MAP_VERSION_MAGIC)) ||
            !IsAcceptableClientBuild(header.buildMagic))
    {
        sLog.outError("Map file '%s' is non-compatible version (outdated?). Please, create new using ad.exe program.", tmp);
        delete[] tmp;
        fclose(pf);
        return false;
    }

    delete[] tmp;
    fclose(pf);
    return true;
}
