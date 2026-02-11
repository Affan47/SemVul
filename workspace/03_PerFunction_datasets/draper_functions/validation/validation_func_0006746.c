A_CheckSkullDone(mobj_t * actor)
{
    if (actor->special2.i == 666)
    {
        P_SetMobjState(actor, S_BLOODYSKULLX2);
    }
}
