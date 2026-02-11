PySequence_Contains(PyObject *seq, PyObject *ob)
{
    Py_ssize_t result;
    if (PyType_HasFeature(seq->ob_type, Py_TPFLAGS_HAVE_SEQUENCE_IN)) {
        PySequenceMethods *sqm = seq->ob_type->tp_as_sequence;
        if (sqm != NULL && sqm->sq_contains != NULL)
            return (*sqm->sq_contains)(seq, ob);
    }
    result = _PySequence_IterSearch(seq, ob, PY_ITERSEARCH_CONTAINS);
    return Py_SAFE_DOWNCAST(result, Py_ssize_t, int);
}
