import_copyreg(void)
{
    static PyObject *copyreg_str;
    static PyObject *mod_copyreg = NULL;

    if (!copyreg_str) {
        copyreg_str = PyUnicode_InternFromString("copyreg");
        if (copyreg_str == NULL)
            return NULL;
    }
    if (!mod_copyreg) {
        mod_copyreg = PyImport_Import(copyreg_str);
    }

    Py_XINCREF(mod_copyreg);
    return mod_copyreg;
}
