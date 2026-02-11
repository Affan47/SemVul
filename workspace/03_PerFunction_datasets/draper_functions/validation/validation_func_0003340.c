buffered_peek(buffered *self, PyObject *args)
{
    Py_ssize_t n = 0;
    PyObject *res = NULL;

    CHECK_INITIALIZED(self)
    if (!PyArg_ParseTuple(args, "|n:peek", &n)) {
        return NULL;
    }

    if (!ENTER_BUFFERED(self))
        return NULL;

    if (self->writable) {
        res = buffered_flush_and_rewind_unlocked(self);
        if (res == NULL)
            goto end;
        Py_CLEAR(res);
    }
    res = _bufferedreader_peek_unlocked(self, n);

end:
    LEAVE_BUFFERED(self)
    return res;
}
