PyBuffer_New(Py_ssize_t size)
{
    PyObject *o;
    PyBufferObject * b;

    if (size < 0) {
        PyErr_SetString(PyExc_ValueError,
                        "size must be zero or positive");
        return NULL;
    }
    if (sizeof(*b) > PY_SSIZE_T_MAX - size) {

        return PyErr_NoMemory();
    }

    o = (PyObject *)PyObject_MALLOC(sizeof(*b) + size);
    if ( o == NULL )
        return PyErr_NoMemory();
    b = (PyBufferObject *) PyObject_INIT(o, &PyBuffer_Type);

    b->b_base = NULL;
    b->b_ptr = (void *)(b + 1);
    b->b_size = size;
    b->b_offset = 0;
    b->b_readonly = 0;
    b->b_hash = -1;

    return o;
}
