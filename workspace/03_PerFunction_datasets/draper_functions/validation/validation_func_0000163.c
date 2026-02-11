posix_chmod(PyObject *self, PyObject *args)
{
    char *path = NULL;
    int i;
    int res;
#ifdef MS_WINDOWS
    DWORD attr;
    PyUnicodeObject *po;
    if (PyArg_ParseTuple(args, "Ui|:chmod", &po, &i)) {
        Py_BEGIN_ALLOW_THREADS
        attr = GetFileAttributesW(PyUnicode_AS_UNICODE(po));
        if (attr != 0xFFFFFFFF) {
            if (i & _S_IWRITE)
                attr &= ~FILE_ATTRIBUTE_READONLY;
            else
                attr |= FILE_ATTRIBUTE_READONLY;
            res = SetFileAttributesW(PyUnicode_AS_UNICODE(po), attr);
        }
        else
            res = 0;
        Py_END_ALLOW_THREADS
        if (!res)
            return win32_error_unicode("chmod",
                                       PyUnicode_AS_UNICODE(po));
        Py_INCREF(Py_None);
        return Py_None;
    }


    PyErr_Clear();

    if (!PyArg_ParseTuple(args, "eti:chmod", Py_FileSystemDefaultEncoding,
                          &path, &i))
        return NULL;
    Py_BEGIN_ALLOW_THREADS
    attr = GetFileAttributesA(path);
    if (attr != 0xFFFFFFFF) {
        if (i & _S_IWRITE)
            attr &= ~FILE_ATTRIBUTE_READONLY;
        else
            attr |= FILE_ATTRIBUTE_READONLY;
        res = SetFileAttributesA(path, attr);
    }
    else
        res = 0;
    Py_END_ALLOW_THREADS
    if (!res) {
        win32_error("chmod", path);
        PyMem_Free(path);
        return NULL;
    }
    PyMem_Free(path);
    Py_INCREF(Py_None);
    return Py_None;
#else
    if (!PyArg_ParseTuple(args, "eti:chmod", Py_FileSystemDefaultEncoding,
                          &path, &i))
        return NULL;
    Py_BEGIN_ALLOW_THREADS
    res = chmod(path, i);
    Py_END_ALLOW_THREADS
    if (res < 0)
        return posix_error_with_allocated_filename(path);
    PyMem_Free(path);
    Py_INCREF(Py_None);
    return Py_None;
#endif
}
