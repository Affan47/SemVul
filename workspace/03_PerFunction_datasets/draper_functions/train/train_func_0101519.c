A_CheckTargetVisible2(mobj_t* actor)
{
    if(!actor->target || actor->target->health <= 0 ||
        !P_CheckSight(actor, actor->target))
    {
        P_SetMobjState(actor, actor->info->seestate);
    }
}
