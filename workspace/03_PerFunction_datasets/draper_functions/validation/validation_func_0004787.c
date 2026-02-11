csv_writer(PyObject *module, PyObject *args, PyObject *keyword_args)
{
    PyObject * output_file, * dialect = NULL;
    WriterObj * self = PyObject_GC_New(WriterObj, &Writer_Type);
    _Py_IDENTIFIER(write);

    if (!self)
        return NULL;

    self->dialect = NULL;
    self->writeline = NULL;

    self->rec = NULL;
    self->rec_size = 0;
    self->rec_len = 0;
    self->num_fields = 0;

    if (!PyArg_UnpackTuple(args, "", 1, 2, &output_file, &dialect)) {
        Py_DECREF(self);
        return NULL;
    }
    self->writeline = _PyObject_GetAttrId(output_file, &PyId_write);
    if (self->writeline == NULL || !PyCallable_Check(self->writeline)) {
        PyErr_SetString(PyExc_TypeError,
                        "argument 1 must have a \"write\" method");
        Py_DECREF(self);
        return NULL;
    }
    self->dialect = (DialectObj *)_call_dialect(dialect, keyword_args);
    if (self->dialect == NULL) {
        Py_DECREF(self);
        return NULL;
    }
    PyObject_GC_Track(self);
    return (PyObject *)self;
}
