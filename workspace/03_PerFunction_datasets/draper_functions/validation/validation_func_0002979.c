SCR_showBandwidth (void) {
    static perftest_t *test = NULL;
    if (!test) {
        test = get_perftest("bandwidth");
        if (!test)
            return;
        test->is_timerate = true;
        test->cvar = cl_drawbandwidth;
        strcpy (test->format, "%2.2fkibps");
        test->scale = 1.0f/1024.0f;
    }

    test->counter += c_incoming_bytes;
    c_incoming_bytes = 0;
}
