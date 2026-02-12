builtin_chr_impl(PyObject *module, int i)

{
    return PyUnicode_FromOrdinal(i);
}
