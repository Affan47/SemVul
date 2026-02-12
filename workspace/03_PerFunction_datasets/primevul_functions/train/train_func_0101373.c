static Token *expand_id(Token * tline)
{
    Token *cur, *oldnext = NULL;

    if (!tline || !tline->next)
        return tline;

    cur = tline;
    while (cur->next &&
           (cur->next->type == TOK_ID ||
            cur->next->type == TOK_PREPROC_ID
            || cur->next->type == TOK_NUMBER))
        cur = cur->next;


    if (cur == tline)
        return tline;

    if (cur) {
        oldnext = cur->next;
        cur->next = NULL;
    }

    tline = expand_smacro(tline);

    if (cur) {

        cur = tline;
        while (cur && cur->next)
            cur = cur->next;
        if (cur)
            cur->next = oldnext;
    }

    return tline;
}
