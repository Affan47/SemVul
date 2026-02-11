mm_openssl_rand(PyObject *self, PyObject *args, PyObject *kwdict)
{
        static char *kwlist[] = { "n", NULL };
        int bytes;
        PyObject *result;
        int r;

        if (!PyArg_ParseTupleAndKeywords(args, kwdict, "i:openssl_rand",
                                         kwlist, &bytes))
                return NULL;

        if (bytes < 0) {
                TYPE_ERR("n must be >= 0");
        }

        if (!(result = PyString_FromStringAndSize(NULL,bytes))) {
                PyErr_NoMemory(); return NULL;
        }

        Py_BEGIN_ALLOW_THREADS
        r = RAND_bytes(PyString_AS_USTRING(result), bytes);
        Py_END_ALLOW_THREADS

        if (!r) {
                Py_DECREF(result);
                mm_SSL_ERR(1);
                return NULL;
        }

        return result;
}
