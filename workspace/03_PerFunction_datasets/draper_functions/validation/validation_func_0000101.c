cm_free(void *dp)
{
    CHUNK           *cp;

    if (!dp)
        return;
    cp = DPTOCP(dp);
    if (cp->magic != MAGIC)
    {
        error_raw
        (
            "%s: %d: bad free %08lX (bug)",
            __FILE__,
            __LINE__,
            (unsigned long)dp
        );
        return;
    }
    cp->prev->next = cp->next;
    cp->next->prev = cp->prev;
    cp->next = 0;
    cp->prev = 0;
    cp->magic = 0;
    r_free(cp);
}
