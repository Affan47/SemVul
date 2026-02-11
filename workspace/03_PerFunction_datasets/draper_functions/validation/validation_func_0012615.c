make_array(PyTypeObject *arraytype, char typecode, PyObject *items)
{
    PyObject *new_args;
    PyObject *array_obj;
    PyObject *typecode_obj;

    assert(arraytype != NULL);
    assert(items != NULL);

    typecode_obj = PyUnicode_FromOrdinal(typecode);
    if (typecode_obj == NULL)
        return NULL;

    new_args = PyTuple_New(2);
    if (new_args == NULL)
        return NULL;
    Py_INCREF(items);
    PyTuple_SET_ITEM(new_args, 0, typecode_obj);
    PyTuple_SET_ITEM(new_args, 1, items);

    array_obj = array_new(arraytype, new_args, NULL);
    Py_DECREF(new_args);
    if (array_obj == NULL)
        return NULL;

    return array_obj;
}
