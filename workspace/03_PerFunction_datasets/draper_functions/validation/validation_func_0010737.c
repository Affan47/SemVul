repeat_dealloc(repeatobject *ro)
{
    PyObject_GC_UnTrack(ro);
    Py_XDECREF(ro->element);
    Py_TYPE(ro)->tp_free(ro);
}
