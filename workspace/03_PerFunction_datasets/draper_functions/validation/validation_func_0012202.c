PyThreadState_Delete(PyThreadState *tstate)
{
    if (tstate == _PyThreadState_Current)
        Py_FatalError("PyThreadState_Delete: tstate is still current");
    tstate_delete_common(tstate);
#ifdef WITH_THREAD
    if (autoInterpreterState && PyThread_get_key_value(autoTLSkey) == tstate)
        PyThread_delete_key_value(autoTLSkey);
#endif
}
