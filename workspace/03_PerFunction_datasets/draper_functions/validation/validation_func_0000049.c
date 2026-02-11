InitMapMusicInfo(void)
{
    int i;

    for (i = 0; i < 99; i++)
    {
        strcpy(MapInfo[i].songLump, DEFAULT_SONG_LUMP);
    }
    MapCount = 98;
}
