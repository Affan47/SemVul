combinations_next(combinationsobject *co)
{
    PyObject *elem;
    PyObject *oldelem;
    PyObject *pool = co->pool;
    Py_ssize_t *indices = co->indices;
    PyObject *result = co->result;
    Py_ssize_t n = PyTuple_GET_SIZE(pool);
    Py_ssize_t r = co->r;
    Py_ssize_t i, j, index;

    if (co->stopped)
        return NULL;

    if (result == NULL) {

        result = PyTuple_New(r);
        if (result == NULL)
            goto empty;
        co->result = result;
        for (i=0; i<r ; i++) {
            index = indices[i];
            elem = PyTuple_GET_ITEM(pool, index);
            Py_INCREF(elem);
            PyTuple_SET_ITEM(result, i, elem);
        }
    } else {

        if (Py_REFCNT(result) > 1) {
            PyObject *old_result = result;
            result = PyTuple_New(r);
            if (result == NULL)
                goto empty;
            co->result = result;
            for (i=0; i<r ; i++) {
                elem = PyTuple_GET_ITEM(old_result, i);
                Py_INCREF(elem);
                PyTuple_SET_ITEM(result, i, elem);
            }
            Py_DECREF(old_result);
        }


        assert(r == 0 || Py_REFCNT(result) == 1);


        for (i=r-1 ; i >= 0 && indices[i] == i+n-r ; i--)
            ;


        if (i < 0)
            goto empty;


        indices[i]++;
        for (j=i+1 ; j<r ; j++)
            indices[j] = indices[j-1] + 1;


        for ( ; i<r ; i++) {
            index = indices[i];
            elem = PyTuple_GET_ITEM(pool, index);
            Py_INCREF(elem);
            oldelem = PyTuple_GET_ITEM(result, i);
            PyTuple_SET_ITEM(result, i, elem);
            Py_DECREF(oldelem);
        }
    }

    Py_INCREF(result);
    return result;

empty:
    co->stopped = 1;
    return NULL;
}
