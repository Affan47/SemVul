eval_re_match_str(struct state *state, struct regexp *rx,
                              const char *str) {
    int r;

    if (str == NULL)
        str = "";

    r = regexp_match(rx, str, strlen(str), 0, NULL);
    if (r == -2) {
        STATE_ERROR(state, PATHX_EINTERNAL);
    } else if (r == -3) {


        assert(false);
    }
    return r == strlen(str);
}
