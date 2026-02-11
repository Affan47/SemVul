read(hsStream* S) {
    bool hasData = true;
    if (S->getVer().isLive() || S->getVer().isHexIsle())
        hasData = S->readBool();

    if (hasData) {
        for (int y=0; y<4; y++)
            for (int x=0; x<4; x++)
                data[y][x] = S->readFloat();
    } else {
        Reset();
    }
}
