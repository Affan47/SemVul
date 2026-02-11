proxy_setitem(PyWeakReference *proxy, PyObject *key, PyObject *value)
{
    if (!proxy_checkref(proxy))
        return -1;

    if (value == NULL)
        return PyObject_DelItem(PyWeakref_GET_OBJECT(proxy), key);
    else
        return PyObject_SetItem(PyWeakref_GET_OBJECT(proxy), key, value);
}
