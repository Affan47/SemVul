session_new_id()
{
    const char *base;
    int now = time(NULL);
    if (now != session_id_time) {
        session_id_time = now;
        session_id_count = 0;
    }
    ++session_id_count;
    base = config_getstring(IMAPOPT_SYSLOG_PREFIX);
    if (!base) base = config_servername;
    snprintf(session_id_buf, MAX_SESSIONID_SIZE, "%.128s-%d-%d-%d",
             base, getpid(), session_id_time, session_id_count);
}
