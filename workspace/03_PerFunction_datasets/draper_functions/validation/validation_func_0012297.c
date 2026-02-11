Pdata_dealloc(Pdata *self)
{
    Py_ssize_t i;
    PyObject **p;

    for (i = self->length, p = self->data; --i >= 0; p++) {
        Py_DECREF(*p);
    }
    if (self->data)
        free(self->data);
    PyObject_Del(self);
}
