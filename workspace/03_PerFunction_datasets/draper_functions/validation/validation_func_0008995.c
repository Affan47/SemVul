A_Look(mobj_t * actor)
{
    mobj_t *targ;

    actor->threshold = 0;
    targ = actor->subsector->sector->soundtarget;
    if (targ && (targ->flags & MF_SHOOTABLE))
    {
        actor->target = targ;
        if (actor->flags & MF_AMBUSH)
        {
            if (P_CheckSight(actor, actor->target))
                goto seeyou;
        }
        else
            goto seeyou;
    }


    if (!P_LookForPlayers(actor, false))
        return;


  seeyou:
    if (actor->info->seesound)
    {
        int sound;


        sound = actor->info->seesound;
        if (actor->flags2 & MF2_BOSS)
        {
            S_StartSound(NULL, sound);
        }
        else
        {
            S_StartSound(actor, sound);
        }
    }
    P_SetMobjState(actor, actor->info->seestate);
}
