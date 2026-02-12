handle_system_exit(void)
{
    PyObject *exception, *value, *tb;
    int exitcode = 0;

    if (Py_InspectFlag)


        return;

    PyErr_Fetch(&exception, &value, &tb);
    fflush(stdout);
    if (value == NULL || value == Py_None)
        goto done;
    if (PyExceptionInstance_Check(value)) {

        _Py_IDENTIFIER(code);
        PyObject *code = _PyObject_GetAttrId(value, &PyId_code);
        if (code) {
            Py_DECREF(value);
            value = code;
            if (value == Py_None)
                goto done;
        }


    }
    if (PyLong_Check(value))
        exitcode = (int)PyLong_AsLong(value);
    else {
        PyObject *sys_stderr = _PySys_GetObjectId(&PyId_stderr);


        PyErr_Clear();
        if (sys_stderr != NULL && sys_stderr != Py_None) {
            PyFile_WriteObject(value, sys_stderr, Py_PRINT_RAW);
        } else {
            PyObject_Print(value, stderr, Py_PRINT_RAW);
            fflush(stderr);
        }
        PySys_WriteStderr("\n");
        exitcode = 1;
    }
 done:


    PyErr_Restore(exception, value, tb);
    PyErr_Clear();
    Py_Exit(exitcode);

}
