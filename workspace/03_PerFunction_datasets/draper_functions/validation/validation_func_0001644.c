latex_analyse_errors (GuLatex* lc) {
    gchar* result = NULL;
    GError* err = NULL;
    GRegex* match_str = NULL;
    GMatchInfo* match_info;

    if (! (match_str = g_regex_new (":(\\d+):", G_REGEX_DOTALL, 0, &err))) {
        slog (L_ERROR, "g_regex_new (): %s\n", err->message);
        g_error_free (err);
        return;
    }

    if (lc->compilelog == NULL) printf("null\n");

    if (g_regex_match (match_str, lc->compilelog, 0, &match_info)) {
        gint count = 0;
        while (g_match_info_matches (match_info)) {
            if (count + 1 == BUFSIZ) break;
            result = g_match_info_fetch (match_info, 1);
            lc->errorlines[count++] = atoi (result);
            g_free (result);
            g_match_info_next (match_info, NULL);
        }
    }
    if (!lc->errorlines[0])
        lc->errorlines[0] = -1;
    g_match_info_free (match_info);
    g_regex_unref (match_str);
}
