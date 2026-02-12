builtin_format_impl(PyObject *module, PyObject *value, PyObject *format_spec)

{
    return PyObject_Format(value, format_spec);
}
