show_warning(PyObject *filename, int lineno, PyObject *text, PyObject
                *category, PyObject *sourceline)
{
    PyObject *f_stderr;
    PyObject *name;
    char lineno_str[128];
    _Py_IDENTIFIER(__name__);

    PyOS_snprintf(lineno_str, sizeof(lineno_str), ":%d: ", lineno);

    name = _PyObject_GetAttrId(category, &PyId___name__);
    if (name == NULL)
        return;

    f_stderr = PySys_GetObject("stderr");
    if (f_stderr == NULL) {
        fprintf(stderr, "lost sys.stderr\n");
        Py_DECREF(name);
        return;
    }


    PyFile_WriteObject(filename, f_stderr, Py_PRINT_RAW);
    PyFile_WriteString(lineno_str, f_stderr);
    PyFile_WriteObject(name, f_stderr, Py_PRINT_RAW);
    PyFile_WriteString(": ", f_stderr);
    PyFile_WriteObject(text, f_stderr, Py_PRINT_RAW);
    PyFile_WriteString("\n", f_stderr);
    Py_XDECREF(name);


    if (sourceline) {
        char *source_line_str = _PyUnicode_AsString(sourceline);
        if (source_line_str == NULL)
                return;
        while (*source_line_str == ' ' || *source_line_str == '\t' ||
                *source_line_str == '\014')
            source_line_str++;

        PyFile_WriteString(source_line_str, f_stderr);
        PyFile_WriteString("\n", f_stderr);
    }
    else
        if (_Py_DisplaySourceLine(f_stderr, filename, lineno, 2) < 0)
                return;
    PyErr_Clear();
}
