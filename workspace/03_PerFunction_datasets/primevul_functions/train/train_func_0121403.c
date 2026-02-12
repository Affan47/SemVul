decoding_fgets(char *s, int size, struct tok_state *tok)
{
    char *line = NULL;
    int badchar = 0;
    for (;;) {
        if (tok->decoding_state == STATE_NORMAL) {


            line = fp_readl(s, size, tok);
            break;
        } else if (tok->decoding_state == STATE_RAW) {

            line = Py_UniversalNewlineFgets(s, size,
                                            tok->fp, NULL);
            break;
        } else {


            if (!check_bom(fp_getc, fp_ungetc, fp_setreadl, tok))
                return error_ret(tok);
            assert(tok->decoding_state != STATE_INIT);
        }
    }
    if (line != NULL && tok->lineno < 2 && !tok->read_coding_spec) {
        if (!check_coding_spec(line, strlen(line), tok, fp_setreadl)) {
            return error_ret(tok);
        }
    }
#ifndef PGEN


    if (line && !tok->encoding) {
        unsigned char *c;
        int length;
        for (c = (unsigned char *)line; *c; c += length)
            if (!(length = valid_utf8(c))) {
                badchar = *c;
                break;
            }
    }
    if (badchar) {


        PyErr_Format(PyExc_SyntaxError,
                "Non-UTF-8 code starting with '\\x%.2x' "
                "in file %U on line %i, "
                "but no encoding declared; "
                "see http://python.org/dev/peps/pep-0263/ for details",
                badchar, tok->filename, tok->lineno + 1);
        return error_ret(tok);
    }
#endif
    return line;
}
