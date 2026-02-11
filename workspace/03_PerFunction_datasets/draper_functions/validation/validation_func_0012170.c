P_TestMobjLocation(mobj_t * mobj)
{
    int flags;

    flags = mobj->flags;
    mobj->flags &= ~MF_PICKUP;
    if (P_CheckPosition(mobj, mobj->x, mobj->y))
    {
        mobj->flags = flags;
        if ((mobj->z < mobj->floorz)
            || (mobj->z + mobj->height > mobj->ceilingz))
        {
            return (false);
        }
        return (true);
    }
    mobj->flags = flags;
    return (false);
}
