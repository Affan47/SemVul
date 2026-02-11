initxxsubtype(void)
{
    PyObject *m;


    spamdict_type.tp_base = &PyDict_Type;
    if (PyType_Ready(&spamdict_type) < 0)
        return;

    spamlist_type.tp_base = &PyList_Type;
    if (PyType_Ready(&spamlist_type) < 0)
        return;

    m = Py_InitModule3("xxsubtype",
                       xxsubtype_functions,
                       xxsubtype__doc__);
    if (m == NULL)
        return;

    if (PyType_Ready(&spamlist_type) < 0)
        return;
    if (PyType_Ready(&spamdict_type) < 0)
        return;

    Py_INCREF(&spamlist_type);
    if (PyModule_AddObject(m, "spamlist",
                           (PyObject *) &spamlist_type) < 0)
        return;

    Py_INCREF(&spamdict_type);
    if (PyModule_AddObject(m, "spamdict",
                           (PyObject *) &spamdict_type) < 0)
        return;
}
