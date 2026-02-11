wait_for_thread_shutdown(void)
{
#ifdef WITH_THREAD
    _Py_IDENTIFIER(_shutdown);
    PyObject *result;
    PyThreadState *tstate = PyThreadState_GET();
    PyObject *threading = PyMapping_GetItemString(tstate->interp->modules,
                                                  "threading");
    if (threading == NULL) {

        PyErr_Clear();
        return;
    }
    result = _PyObject_CallMethodId(threading, &PyId__shutdown, "");
    if (result == NULL) {
        PyErr_WriteUnraisable(threading);
    }
    else {
        Py_DECREF(result);
    }
    Py_DECREF(threading);
#endif
}
