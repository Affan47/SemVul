runprof(struct pma *pma, int *keys, int nkeys, int ntrials)
{
    int i;
    struct timespec start_time;
    struct timespec end_time;
    struct timespec diff_time;

    fprintf(stderr, ".\n");

    clock_gettime(CLOCK_MONOTONIC, &start_time);
    for (i=0; i < ntrials; i++)
    {
        struct leaf *leaf;

        int which = i % nkeys;
        leaf = pma_search(pma, keys[which]);
        if (leaf != NULL && leaf->key != keys[which])
        {
            printf("Could not recover %d (got %d)\n", keys[which],
                leaf->key);
        }
    }
    clock_gettime(CLOCK_MONOTONIC, &end_time);
    timespec_sub(&end_time, &start_time, &diff_time);
    return diff_time.tv_sec * 1000000 + (diff_time.tv_nsec / 1000);
}
