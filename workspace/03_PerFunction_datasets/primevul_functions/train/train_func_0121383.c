parsestrplus(struct compiling *c, const node *n)
{
    int bytesmode = 0;
    PyObject *bytes_str = NULL;
    int i;

    FstringParser state;
    FstringParser_Init(&state);

    for (i = 0; i < NCH(n); i++) {
        int this_bytesmode;
        int this_rawmode;
        PyObject *s;
        const char *fstr;
        Py_ssize_t fstrlen = -1;

        REQ(CHILD(n, i), STRING);
        if (parsestr(c, CHILD(n, i), &this_bytesmode, &this_rawmode, &s,
                     &fstr, &fstrlen) != 0)
            goto error;


        if (i != 0 && bytesmode != this_bytesmode) {
            ast_error(c, n, "cannot mix bytes and nonbytes literals");

            Py_XDECREF(s);
            goto error;
        }
        bytesmode = this_bytesmode;

        if (fstr != NULL) {
            int result;
            assert(s == NULL && !bytesmode);

            result = FstringParser_ConcatFstring(&state, &fstr, fstr+fstrlen,
                                                 this_rawmode, 0, c, n);
            if (result < 0)
                goto error;
        } else {

            assert(s != NULL && fstr == NULL);

            assert(bytesmode ? PyBytes_CheckExact(s) :
                   PyUnicode_CheckExact(s));

            if (bytesmode) {

                if (i == 0) {

                    bytes_str = s;
                } else {
                    PyBytes_ConcatAndDel(&bytes_str, s);
                    if (!bytes_str)
                        goto error;
                }
            } else {

                if (FstringParser_ConcatAndDel(&state, s) < 0)
                    goto error;
            }
        }
    }
    if (bytesmode) {

        if (PyArena_AddPyObject(c->c_arena, bytes_str) < 0)
            goto error;
        return Bytes(bytes_str, LINENO(n), n->n_col_offset, c->c_arena);
    }


    assert(bytes_str == NULL);

    return FstringParser_Finish(&state, c, n);

error:
    Py_XDECREF(bytes_str);
    FstringParser_Dealloc(&state);
    return NULL;
}
