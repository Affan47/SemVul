pattern_fullmatch(PatternObject* self, PyObject* args, PyObject* kw)
{
    SRE_STATE state;
    Py_ssize_t status;

    PyObject *string = NULL, *string2 = NULL;
    Py_ssize_t start = 0;
    Py_ssize_t end = PY_SSIZE_T_MAX;
    static char* kwlist[] = { "string", "pos", "endpos", "pattern", NULL };
    if (!PyArg_ParseTupleAndKeywords(args, kw, "|Onn$O:fullmatch", kwlist,
                                     &string, &start, &end, &string2))
        return NULL;

    string = fix_string_param(string, string2, "pattern");
    if (!string)
        return NULL;

    string = state_init(&state, self, string, start, end);
    if (!string)
        return NULL;

    state.ptr = state.start;

    TRACE(("|%p|%p|FULLMATCH\n", PatternObject_GetCode(self), state.ptr));

    status = sre_match(&state, PatternObject_GetCode(self), 1);

    TRACE(("|%p|%p|END\n", PatternObject_GetCode(self), state.ptr));
    if (PyErr_Occurred())
        return NULL;

    state_fini(&state);

    return pattern_new_match(self, &state, status);
}
