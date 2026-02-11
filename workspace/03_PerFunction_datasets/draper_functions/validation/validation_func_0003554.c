init_stats()
{
    int i;

    init_clocks();
    for (i = 0; i < MAX_INTERNAL_FLAGS; i++)
	Internal_flags[i] = 0;
    for (i = 0; i < MACE_MAX_STATS; i++)
	MACE_Stats[i] = 0;
}
