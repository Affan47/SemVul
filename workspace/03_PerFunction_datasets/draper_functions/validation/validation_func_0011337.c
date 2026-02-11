SB_PaletteFlash(boolean forceChange)
{
    static int sb_palette = 0;
    int palette;
    byte *pal;

    if (forceChange)
    {
        sb_palette = -1;
    }
    if (gamestate == GS_LEVEL)
    {
        CPlayer = &players[consoleplayer];
        if (CPlayer->poisoncount)
        {
            palette = 0;
            palette = (CPlayer->poisoncount + 7) >> 3;
            if (palette >= NUMPOISONPALS)
            {
                palette = NUMPOISONPALS - 1;
            }
            palette += STARTPOISONPALS;
        }
        else if (CPlayer->damagecount)
        {
            palette = (CPlayer->damagecount + 7) >> 3;
            if (palette >= NUMREDPALS)
            {
                palette = NUMREDPALS - 1;
            }
            palette += STARTREDPALS;
        }
        else if (CPlayer->bonuscount)
        {
            palette = (CPlayer->bonuscount + 7) >> 3;
            if (palette >= NUMBONUSPALS)
            {
                palette = NUMBONUSPALS - 1;
            }
            palette += STARTBONUSPALS;
        }
        else if (CPlayer->mo->flags2 & MF2_ICEDAMAGE)
        {
            palette = STARTICEPAL;
        }
        else
        {
            palette = 0;
        }
    }
    else
    {
        palette = 0;
    }
    if (palette != sb_palette)
    {
        sb_palette = palette;
        pal = (byte *) W_CacheLumpNum(PlayPalette, PU_CACHE) + palette * 768;
        I_SetPalette(pal);
    }
}
