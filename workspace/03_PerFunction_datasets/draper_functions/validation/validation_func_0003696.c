PyObject_IsInstance(PyObject *inst, PyObject *cls)
{
    static PyObject *name = NULL;


    if (Py_TYPE(inst) == (PyTypeObject *)cls)
        return 1;

    if (PyTuple_Check(cls)) {
        Py_ssize_t i;
        Py_ssize_t n;
        int r = 0;

        if (Py_EnterRecursiveCall(" in __instancecheck__"))
            return -1;
        n = PyTuple_GET_SIZE(cls);
        for (i = 0; i < n; ++i) {
            PyObject *item = PyTuple_GET_ITEM(cls, i);
            r = PyObject_IsInstance(inst, item);
            if (r != 0)

                break;
        }
        Py_LeaveRecursiveCall();
        return r;
    }

    if (!(PyClass_Check(cls) || PyInstance_Check(cls))) {
        PyObject *checker;
        checker = _PyObject_LookupSpecial(cls, "__instancecheck__", &name);
        if (checker != NULL) {
            PyObject *res;
            int ok = -1;
            if (Py_EnterRecursiveCall(" in __instancecheck__")) {
                Py_DECREF(checker);
                return ok;
            }
            res = PyObject_CallFunctionObjArgs(checker, inst, NULL);
            Py_LeaveRecursiveCall();
            Py_DECREF(checker);
            if (res != NULL) {
                ok = PyObject_IsTrue(res);
                Py_DECREF(res);
            }
            return ok;
        }
        else if (PyErr_Occurred())
            return -1;
    }
    return recursive_isinstance(inst, cls);
}
