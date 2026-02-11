PrintError(char *msg, ...)
{
    char buf[512];
    PyObject *f = PySys_GetObject("stderr");
    va_list marker;

    va_start(marker, msg);
    vsnprintf(buf, sizeof(buf), msg, marker);
    va_end(marker);
    if (f != NULL && f != Py_None)
        PyFile_WriteString(buf, f);
    PyErr_Print();
}
