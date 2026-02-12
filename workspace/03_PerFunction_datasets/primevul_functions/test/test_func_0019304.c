AuditFlush(OsTimerPtr timer, CARD32 now, void *arg)
{
    char *prefix;

    if (nrepeat > 0) {
        prefix = AuditPrefix();
        ErrorF("%slast message repeated %d times\n",
               prefix != NULL ? prefix : "", nrepeat);
        nrepeat = 0;
        free(prefix);
        return AUDIT_TIMEOUT;
    }
    else {

        oldlen = -1;
        return 0;
    }
}
