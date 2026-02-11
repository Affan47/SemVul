hostlist_push_list(hostlist_t h1, hostlist_t h2)
{
    int i, n = 0;

    if (h2 == NULL)
        return 0;

    LOCK_HOSTLIST(h2);

    for (i = 0; i < h2->nranges; i++)
        n += hostlist_push_range(h1, h2->hr[i]);

    UNLOCK_HOSTLIST(h2);

    return n;
}
