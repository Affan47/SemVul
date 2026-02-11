G_DoWorldDone (void)
{
    int temp_leveltime = leveltime;
    boolean temp_shadow = false;
    boolean temp_mvis   = false;

    gamestate = GS_LEVEL;
    gamemap = destmap;


    G_LoadPath(destmap);
    if (!deathmatch)
    {

        if(players[0].mo->flags & MF_SHADOW)
            temp_shadow = true;
        if(players[0].mo->flags & MF_MVIS)
            temp_mvis = true;
    }
    G_DoLoadGame(false);


    leveltime = temp_leveltime;

    if(!deathmatch)
    {

        players[0].mo->flags &= ~(MF_SHADOW|MF_MVIS);
        if(temp_shadow)
            players[0].mo->flags |= MF_SHADOW;
        if(temp_mvis)
            players[0].mo->flags |= MF_MVIS;


        G_RiftPlayer();
        G_DoSaveGame(savepathtemp);
        M_SaveMisObj(savepathtemp);
    }

    gameaction = ga_nothing;
    viewactive = true;
}
