tail_contains(PyObject *list, int whence, PyObject *o) {
    Py_ssize_t j, size;
    size = PyList_GET_SIZE(list);

    for (j = whence+1; j < size; j++) {
        if (PyList_GET_ITEM(list, j) == o)
            return 1;
    }
    return 0;
}
