_PyArg_ParseTupleAndKeywords_SizeT(PyObject *args,
                                  PyObject *keywords,
                                  const char *format,
                                  char **kwlist, ...)
{
    int retval;
    va_list va;

    if ((args == NULL || !PyTuple_Check(args)) ||
        (keywords != NULL && !PyDict_Check(keywords)) ||
        format == NULL ||
        kwlist == NULL)
    {
        PyErr_BadInternalCall();
        return 0;
    }

    va_start(va, kwlist);
    retval = vgetargskeywords(args, keywords, format,
                              kwlist, &va, FLAG_SIZE_T);
    va_end(va);
    return retval;
}
