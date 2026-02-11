wrap_gobj(PyObject *self, PyObject *args)
{
    void *addr;
    GObject *obj;

    if (!PyArg_ParseTuple(args, "l", &addr))
        return NULL;

    if (!G_IS_OBJECT(addr))
        return NULL;

    obj = G_OBJECT(addr);

    if (!obj)
        return NULL;

    return pygobject_new(obj);
}
