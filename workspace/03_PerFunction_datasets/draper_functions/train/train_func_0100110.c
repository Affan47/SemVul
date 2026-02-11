act_current_sche()
{
    int i;

    pthread_t tid;

    tid = pthread_self();

    for (i = 0; i < act_sche_num; i ++) {
        act_sche_t *sche = act_sches[i];

        if (sche != NULL && sche->tid == tid) {
            return sche;
        }
    }

    return NULL;
}
