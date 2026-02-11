mem_usage()
{
    FILE *fp;
    char buf[160];
    int i;

    fp = fopen("/proc/meminfo", "r");
    if (!fp)
        return;
    for (i = 0; i < MT_NUM; i++)
    {
        mt[i].valid = 0;
        mt[i].val = 0;
    }

    while ((fgets(buf, sizeof(buf), fp)) != NULL)
    {
        for (i = 0; i < MT_NUM; i++)
        {
            if (!mt[i].valid && mt_match(buf, mt + i))
                break;
        }
    }
    fclose(fp);

    stats.mem.total = mt[MT_MemTotal].val;
    stats.mem.used = mt[MT_MemTotal].val -(mt[MT_MemFree].val +
        mt[MT_Buffers].val + mt[MT_Cached].val + mt[MT_Slab].val);
    stats.swap.total = mt[MT_SwapTotal].val;
    stats.swap.used = mt[MT_SwapTotal].val - mt[MT_SwapFree].val;
}
