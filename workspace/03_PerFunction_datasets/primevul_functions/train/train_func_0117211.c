static void wsgi_release_interpreter(InterpreterObject *handle)
{
    PyThreadState *tstate = NULL;

    PyGILState_STATE state;


    if (*handle->name) {
        tstate = PyThreadState_Get();
        PyEval_ReleaseThread(tstate);
    }
    else
        PyGILState_Release(PyGILState_UNLOCKED);


    state = PyGILState_Ensure();

    Py_DECREF(handle);

    PyGILState_Release(state);
}
