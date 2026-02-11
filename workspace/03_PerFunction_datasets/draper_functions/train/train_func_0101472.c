r_ref_insert(PyObject *o, Py_ssize_t idx, int flag, RFILE *p)
{
    if (o != NULL && flag) {
        PyObject *tmp = PyList_GET_ITEM(p->refs, idx);
        Py_INCREF(o);
        PyList_SET_ITEM(p->refs, idx, o);
        Py_DECREF(tmp);
    }
    return o;
}
