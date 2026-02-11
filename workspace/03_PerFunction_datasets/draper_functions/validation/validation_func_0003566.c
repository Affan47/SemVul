P_ReadSaveGameHeader(void)
{
    int	 i;
    byte a, b, c;
    char vcheck[VERSIONSIZE];
    char read_vcheck[VERSIONSIZE];


    for (i=0; i<SAVESTRINGSIZE; ++i)
        saveg_read8();

    for (i=0; i<VERSIONSIZE; ++i)
        read_vcheck[i] = saveg_read8();

    memset (vcheck,0,sizeof(vcheck));
    sprintf (vcheck,"version %i",DOOM_VERSION);
    if (strcmp(read_vcheck, vcheck) != 0)
	return false;

    gameskill = saveg_read8();
    gameepisode = saveg_read8();
    gamemap = saveg_read8();

    for (i=0 ; i<MAXPLAYERS ; i++)
	playeringame[i] = saveg_read8();


    a = saveg_read8();
    b = saveg_read8();
    c = saveg_read8();
    leveltime = (a<<16) + (b<<8) + c;

    return true;
}
