P_NightmareRespawn (mobj_t* mobj)
{
    fixed_t      x;
    fixed_t      y;
    fixed_t      z;
    mobj_t*      mo;
    mapthing_t*  mthing;

    x = mobj->spawnpoint.x << FRACBITS;
    y = mobj->spawnpoint.y << FRACBITS;


    if (!P_CheckPosition (mobj, x, y) )
        return;


    mo = P_SpawnMobj (mobj->x,
                      mobj->y,
                      mobj->subsector->sector->floorheight , MT_TFOG);

    S_StartSound (mo, sfx_telept);


    mo = P_SpawnMobj (x, y, ONFLOORZ , MT_TFOG);

    S_StartSound (mo, sfx_telept);


    mthing = &mobj->spawnpoint;


    if (mobj->info->flags & MF_SPAWNCEILING)
        z = ONCEILINGZ;
    else
        z = ONFLOORZ;


    mo = P_SpawnMobj (x,y,z, mobj->type);
    mo->spawnpoint = mobj->spawnpoint;
    mo->angle = ANG45 * (mthing->angle/45);

    if (mthing->options & MTF_AMBUSH)
        mo->flags |= MF_AMBUSH;
    if (mthing->options & MTF_STAND)
        mobj->flags |= MF_STAND;
    if (mthing->options & MTF_FRIEND)
        mobj->flags |= MF_ALLY;
    if (mthing->options & MTF_TRANSLUCENT)
        mobj->flags |= MF_SHADOW;
    if (mthing->options & MTF_MVIS)
        mobj->flags |= MF_MVIS;

    mo->reactiontime = 18;


    P_RemoveMobj (mobj);
}
