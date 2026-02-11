Reset()
{
    mode = External;
    type = trpg_Unknown;
    numLayer = -1;
    if (name)
        delete [] name;
    name = NULL;
    useCount = 0;
    sizeX = sizeY = -1;
    addr.file = 0;
    addr.offset = 0;
    addr.row = -1;
    addr.col = -1;
    isMipmap = false;
    storageSize.clear();
    levelOffset.clear();
    handle = -1;
    writeHandle = false;
}
