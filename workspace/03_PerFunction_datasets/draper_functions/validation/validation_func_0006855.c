regexp_match_error(struct state *state, struct lens *lens,
                               int count, struct regexp *r) {
    char *text = NULL;
    char *pat = regexp_escape(r);

    if (state->regs != NULL)
        text = strndup(REG_POS(state), REG_SIZE(state));
    else
        text = strdup("(unknown)");

    if (count == -1) {
        get_error(state, lens, "Failed to match /%s/ with %s", pat, text);
    } else if (count == -2) {
        get_error(state, lens, "Internal error matching /%s/ with %s",
                  pat, text);
    } else if (count == -3) {

        get_error(state, lens, "Syntax error in regexp /%s/", pat);
    }
    free(pat);
    free(text);
}
