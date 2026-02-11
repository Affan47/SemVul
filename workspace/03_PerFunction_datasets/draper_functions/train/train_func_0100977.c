disarm_landmine(struct trap *ttmp)
{
    int fails = try_disarm(ttmp, false);

    if (fails < 2) return fails;
    You("disarm %s land mine.", the_your[ttmp->madeby_u]);
    cnv_trap_obj(LAND_MINE, 1, ttmp);
    return 1;
}
