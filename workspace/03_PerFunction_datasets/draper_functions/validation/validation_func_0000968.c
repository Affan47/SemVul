tupleprint(PyTupleObject *op, FILE *fp, int flags)
{
    Py_ssize_t i;
    Py_BEGIN_ALLOW_THREADS
    fprintf(fp, "(");
    Py_END_ALLOW_THREADS
    for (i = 0; i < Py_SIZE(op); i++) {
        if (i > 0) {
            Py_BEGIN_ALLOW_THREADS
            fprintf(fp, ", ");
            Py_END_ALLOW_THREADS
        }
        if (PyObject_Print(op->ob_item[i], fp, 0) != 0)
            return -1;
    }
    i = Py_SIZE(op);
    Py_BEGIN_ALLOW_THREADS
    if (i == 1)
        fprintf(fp, ",");
    fprintf(fp, ")");
    Py_END_ALLOW_THREADS
    return 0;
}
