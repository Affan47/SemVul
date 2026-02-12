static bool paste_tokens(Token **head, const struct tokseq_match *m,
                         size_t mnum, bool handle_explicit)
{
    Token *tok, *next, **prev_next, **prev_nonspace;
    bool pasted = false;
    char *buf, *p;
    size_t len, i;


    tok = *head;
    prev_next = NULL;

    if (!tok_type_(tok, TOK_WHITESPACE) && !tok_type_(tok, TOK_PASTE))
        prev_nonspace = head;
    else
        prev_nonspace = NULL;

    while (tok && (next = tok->next)) {

        switch (tok->type) {
        case TOK_WHITESPACE:

            while (tok_type_(next, TOK_WHITESPACE))
                next = delete_Token(next);
            tok->next = next;
            break;

        case TOK_PASTE:

            if (!handle_explicit)
                break;
            next = delete_Token(tok);

            while (tok_type_(next, TOK_WHITESPACE))
                next = delete_Token(next);

            if (!pasted)
                pasted = true;


            if (!prev_nonspace)
                nasm_error(ERR_FATAL, "No lvalue found on pasting");


            if (!next) {


                tok = (*prev_nonspace)->next;
                while (tok_type_(tok, TOK_WHITESPACE))
                    tok = delete_Token(tok);
                tok = *prev_nonspace;
                tok->next = NULL;
                break;
            }

            tok = *prev_nonspace;
            while (tok_type_(tok, TOK_WHITESPACE))
                tok = delete_Token(tok);
            len  = strlen(tok->text);
            len += strlen(next->text);

            p = buf = nasm_malloc(len + 1);
            strcpy(p, tok->text);
            p = strchr(p, '\0');
            strcpy(p, next->text);

            delete_Token(tok);

            tok = tokenize(buf);
            nasm_free(buf);

            *prev_nonspace = tok;
            while (tok && tok->next)
                tok = tok->next;

            tok->next = delete_Token(next);


            tok = *prev_nonspace;
            break;

        default:

            for (i = 0; i < mnum; i++) {
                if (!(PP_CONCAT_MATCH(tok, m[i].mask_head)))
                    continue;

                len = 0;
                while (next && PP_CONCAT_MATCH(next, m[i].mask_tail)) {
                    len += strlen(next->text);
                    next = next->next;
                }


                if (tok == next)
                    break;

                len += strlen(tok->text);
                p = buf = nasm_malloc(len + 1);

                strcpy(p, tok->text);
                p = strchr(p, '\0');
                tok = delete_Token(tok);

                while (tok != next) {
                    if (PP_CONCAT_MATCH(tok, m[i].mask_tail)) {
                        strcpy(p, tok->text);
                        p = strchr(p, '\0');
                    }
                    tok = delete_Token(tok);
                }

                tok = tokenize(buf);
                nasm_free(buf);

                if (prev_next)
                    *prev_next = tok;
                else
                    *head = tok;


                while (tok && tok->next)
                    tok = tok->next;
                tok->next = next;

                if (!pasted)
                    pasted = true;


                tok = prev_next ? *prev_next : *head;
            }

            break;
        }

        prev_next = &tok->next;

        if (tok->next &&
            !tok_type_(tok->next, TOK_WHITESPACE) &&
            !tok_type_(tok->next, TOK_PASTE))
            prev_nonspace = prev_next;

        tok = tok->next;
    }

    return pasted;
}
