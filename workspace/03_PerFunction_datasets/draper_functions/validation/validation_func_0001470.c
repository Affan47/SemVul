make_encode_exception(PyObject **exceptionObject,
                                  const char *encoding,
                                  const Py_UNICODE *unicode, Py_ssize_t size,
                                  Py_ssize_t startpos, Py_ssize_t endpos,
                                  const char *reason)
{
    if (*exceptionObject == NULL) {
        *exceptionObject = PyUnicodeEncodeError_Create(
            encoding, unicode, size, startpos, endpos, reason);
    }
    else {
        if (PyUnicodeEncodeError_SetStart(*exceptionObject, startpos))
            goto onError;
        if (PyUnicodeEncodeError_SetEnd(*exceptionObject, endpos))
            goto onError;
        if (PyUnicodeEncodeError_SetReason(*exceptionObject, reason))
            goto onError;
        return;
      onError:
        Py_CLEAR(*exceptionObject);
    }
}
