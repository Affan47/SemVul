void M_ScreenShot (void)
{
    int		i;
    byte*	linear;
    char	lbmname[12];


    linear = screens[2];
    I_ReadScreen (linear);


    strcpy(lbmname,"DOOM00.pcx");

    for (i=0 ; i<=99 ; i++)
    {
	lbmname[4] = i/10 + '0';
	lbmname[5] = i%10 + '0';
	if (access(lbmname,0) == -1)
	    break;
    }
    if (i==100)
	I_Error ("M_ScreenShot: Couldn't create a PCX");


    WritePCXfile (lbmname, linear,
		  SCREENWIDTH, SCREENHEIGHT,
		  W_CacheLumpName ("PLAYPAL",PU_CACHE));

    players[consoleplayer].message = "screen shot";
}
