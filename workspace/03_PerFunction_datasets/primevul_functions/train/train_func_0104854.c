static Token *expand_smacro_noreset(Token *org_tline)
{
    Token *tline;
    bool expanded;
    errhold errhold;

    if (!org_tline)
        return NULL;


    tline = dup_Token(org_tline->next, org_tline);


    expanded = true;

    while (true) {
        static const struct tokseq_match tmatch[] = {
            {
                PP_CONCAT_MASK(TOK_ID)          |
		PP_CONCAT_MASK(TOK_LOCAL_MACRO) |
		PP_CONCAT_MASK(TOK_ENVIRON)     |
                PP_CONCAT_MASK(TOK_PREPROC_ID),
                PP_CONCAT_MASK(TOK_ID)          |
		PP_CONCAT_MASK(TOK_LOCAL_MACRO) |
		PP_CONCAT_MASK(TOK_ENVIRON)     |
                PP_CONCAT_MASK(TOK_PREPROC_ID)  |
                PP_CONCAT_MASK(TOK_NUMBER)
            }
        };
        Token **tail = &tline;


        errhold = nasm_error_hold_push();

        while (*tail)
            expanded |= !!expand_one_smacro(&tail);

         if (!expanded)
            break;


        if (!paste_tokens(&tline, tmatch, ARRAY_SIZE(tmatch), true))
            break;

        nasm_error_hold_pop(errhold, false);
        expanded = false;
    }
    nasm_error_hold_pop(errhold, true);

    if (!tline) {


	tline = new_White(NULL);
    }

    steal_Token(org_tline, tline);
    org_tline->next = tline->next;
    delete_Token(tline);

    return org_tline;
}
