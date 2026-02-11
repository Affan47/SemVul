bytesio_sizeof(bytesio *self, void *unused)
{
    Py_ssize_t res;

    res = sizeof(bytesio);
    if (self->buf)
        res += self->buf_size;
    return PyLong_FromSsize_t(res);
}
