static void do_pragma_preproc(Token *tline)
{

    tline = tline->next;
    skip_white_(tline);
    if (!tline)
        return;

    (void)tline;
}
