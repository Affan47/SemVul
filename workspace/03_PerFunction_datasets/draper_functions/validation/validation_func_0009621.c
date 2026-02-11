posix_ftruncate(PyObject *self, PyObject *args)
{
    int fd;
    off_t length;
    int res;
    PyObject *lenobj;

    if (!PyArg_ParseTuple(args, "iO:ftruncate", &fd, &lenobj))
        return NULL;

#if !defined(HAVE_LARGEFILE_SUPPORT)
    length = PyInt_AsLong(lenobj);
#else
    length = PyLong_Check(lenobj) ?
        PyLong_AsLongLong(lenobj) : PyInt_AsLong(lenobj);
#endif
    if (PyErr_Occurred())
        return NULL;

    Py_BEGIN_ALLOW_THREADS
    res = ftruncate(fd, length);
    Py_END_ALLOW_THREADS
    if (res < 0)
        return posix_error();
    Py_INCREF(Py_None);
    return Py_None;
}
