parsestrplus(struct compiling *c, const node *n)
{
        PyObject *v;
        int i;
        REQ(CHILD(n, 0), STRING);
        if ((v = parsestr(c, n, STR(CHILD(n, 0)))) != NULL) {

                for (i = 1; i < NCH(n); i++) {
                        PyObject *s;
                        s = parsestr(c, n, STR(CHILD(n, i)));
                        if (s == NULL)
                                goto onError;
                        if (PyBytes_Check(v) && PyBytes_Check(s)) {
                                PyBytes_ConcatAndDel(&v, s);
                                if (v == NULL)
                                    goto onError;
                        }
#ifdef Py_USING_UNICODE
                        else {
                                PyObject *temp;


                                if (PyBytes_Check(s)) {
                                    temp = PyUnicode_FromEncodedObject(s, NULL, "strict");
                                    Py_DECREF(s);
                                    s = temp;
                                }

                                if (PyBytes_Check(v)) {
                                    temp = PyUnicode_FromEncodedObject(v, NULL, "strict");
                                    Py_DECREF(v);
                                    v = temp;
                                }

                                temp = PyUnicode_Concat(v, s);
                                Py_DECREF(s);
                                Py_DECREF(v);
                                v = temp;
                                if (v == NULL)
                                    goto onError;
                        }
#endif
                }
        }
        return v;

 onError:
        Py_XDECREF(v);
        return NULL;
}
