getxattr_common(const char *path, PyObject *name_obj,
                ssize_t (*get)(const char *, const char *, void *, size_t))
{
    PyObject *value;
    const char *name = PyBytes_AS_STRING(name_obj);


    if (!try_getxattr(path, name, get, 128, &value))
        return NULL;
    if (value)
        return value;

    if (!try_getxattr(path, name, get, XATTR_SIZE_MAX, &value))
        return NULL;
    assert(value);
    return value;
}
