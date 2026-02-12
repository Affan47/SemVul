zip_reduce(zipobject *lz, PyObject *Py_UNUSED(ignored))
{

    return Py_BuildValue("OO", Py_TYPE(lz), lz->ittuple);
}
