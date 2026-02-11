read_string_xdigits(ScmPort *port, int ndigs, int key,
                                   int incompletep)
{
    char buf[8];
    int nread;
    ScmChar r;
    SCM_ASSERT(ndigs <= 8);
    r = Scm_ReadXdigitsFromPort(port, ndigs, buf, &nread);
    if (r == SCM_CHAR_INVALID) {
        ScmDString ds;
        int c, i;


        for (;;) {
            if (incompletep) c = Scm_GetbUnsafe(port);
            else c = Scm_GetcUnsafe(port);
            if (c == EOF || c == '"') break;
            if (c == '\\') {
                if (incompletep) c = Scm_GetbUnsafe(port);
                else c = Scm_GetcUnsafe(port);
            }
        }

        Scm_DStringInit(&ds);
        Scm_DStringPutc(&ds, '\\');
        Scm_DStringPutc(&ds, key);
        for (i=0; i<nread; i++) Scm_DStringPutc(&ds, (unsigned char)buf[i]);
        Scm_ReadError(port,
                      "Bad '\\%c' escape sequence in a string literal: %s",
                      key, Scm_DStringGetz(&ds));
    }
    return r;
}
