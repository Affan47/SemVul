GetMobjNum(mobj_t * mobj)
{
    if (mobj == NULL)
    {
        return MOBJ_NULL;
    }
    if (mobj->player && !SavingPlayers)
    {
        return MOBJ_XX_PLAYER;
    }
    return mobj->archiveNum;
}
