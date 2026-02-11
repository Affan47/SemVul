script_handler_es_statement(spif_charptr_t *params)
{
    char *tmp;

    if (params && *params) {
        tmp = spiftool_join(" ", params);
        ns_statement(TermWin.screen, tmp);
        FREE(tmp);
    } else {
        ns_statement(TermWin.screen, NULL);
    }
}
