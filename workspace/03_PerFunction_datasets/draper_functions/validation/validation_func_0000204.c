set_intersection(PySetObject *so, PyObject *other)
{
    PySetObject *result;
    PyObject *key, *it, *tmp;

    if ((PyObject *)so == other)
        return set_copy(so);

    result = (PySetObject *)make_new_set(Py_TYPE(so), NULL);
    if (result == NULL)
        return NULL;

    if (PyAnySet_Check(other)) {
        Py_ssize_t pos = 0;
        setentry *entry;

        if (PySet_GET_SIZE(other) > PySet_GET_SIZE(so)) {
            tmp = (PyObject *)so;
            so = (PySetObject *)other;
            other = tmp;
        }

        while (set_next((PySetObject *)other, &pos, &entry)) {
            int rv = set_contains_entry(so, entry);
            if (rv == -1) {
                Py_DECREF(result);
                return NULL;
            }
            if (rv) {
                if (set_add_entry(result, entry) == -1) {
                    Py_DECREF(result);
                    return NULL;
                }
            }
        }
        return (PyObject *)result;
    }

    it = PyObject_GetIter(other);
    if (it == NULL) {
        Py_DECREF(result);
        return NULL;
    }

    while ((key = PyIter_Next(it)) != NULL) {
        int rv;
        setentry entry;
        long hash = PyObject_Hash(key);

        if (hash == -1) {
            Py_DECREF(it);
            Py_DECREF(result);
            Py_DECREF(key);
            return NULL;
        }
        entry.hash = hash;
        entry.key = key;
        rv = set_contains_entry(so, &entry);
        if (rv == -1) {
            Py_DECREF(it);
            Py_DECREF(result);
            Py_DECREF(key);
            return NULL;
        }
        if (rv) {
            if (set_add_entry(result, &entry) == -1) {
                Py_DECREF(it);
                Py_DECREF(result);
                Py_DECREF(key);
                return NULL;
            }
        }
        Py_DECREF(key);
    }
    Py_DECREF(it);
    if (PyErr_Occurred()) {
        Py_DECREF(result);
        return NULL;
    }
    return (PyObject *)result;
}
