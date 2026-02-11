D_Display(void)
{
    extern boolean askforquit;


    if (setsizeneeded)
    {
        R_ExecuteSetViewSize();
    }


    switch (gamestate)
    {
        case GS_LEVEL:
            if (!gametic)
                break;
            if (automapactive)
                AM_Drawer();
            else
                R_RenderPlayerView(&players[displayplayer]);
            CT_Drawer();
            UpdateState |= I_FULLVIEW;
            SB_Drawer();
            break;
        case GS_INTERMISSION:
            IN_Drawer();
            break;
        case GS_FINALE:
            F_Drawer();
            break;
        case GS_DEMOSCREEN:
            D_PageDrawer();
            break;
    }

    if (testcontrols)
    {
        V_DrawMouseSpeedBox(testcontrols_mousespeed);
    }

    if (paused && !MenuActive && !askforquit)
    {
        if (!netgame)
        {
            V_DrawPatch(160, viewwindowy + 5, W_CacheLumpName(DEH_String("PAUSED"),
                                                              PU_CACHE));
        }
        else
        {
            V_DrawPatch(160, 70, W_CacheLumpName(DEH_String("PAUSED"), PU_CACHE));
        }
    }

    DrawMessage();


    MN_Drawer();


    NetUpdate();


    I_FinishUpdate();
}
