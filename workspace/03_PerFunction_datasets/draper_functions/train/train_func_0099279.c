fcntl_ioctl(PyObject *self, PyObject *args)
{
#define IOCTL_BUFSZ 1024
    int fd;


    unsigned int code;
    int arg;
    int ret;
    char *str;
    Py_ssize_t len;
    int mutate_arg = 1;
    char buf[IOCTL_BUFSZ+1];

    if (PyArg_ParseTuple(args, "O&Iw#|i:ioctl",
                         conv_descriptor, &fd, &code,
                         &str, &len, &mutate_arg)) {
        char *arg;

        if (mutate_arg) {
            if (len <= IOCTL_BUFSZ) {
                memcpy(buf, str, len);
                buf[len] = '\0';
                arg = buf;
            }
            else {
                arg = str;
            }
        }
        else {
            if (len > IOCTL_BUFSZ) {
                PyErr_SetString(PyExc_ValueError,
                    "ioctl string arg too long");
                return NULL;
            }
            else {
                memcpy(buf, str, len);
                buf[len] = '\0';
                arg = buf;
            }
        }
        if (buf == arg) {
            Py_BEGIN_ALLOW_THREADS
            ret = ioctl(fd, code, arg);
            Py_END_ALLOW_THREADS
        }
        else {
            ret = ioctl(fd, code, arg);
        }
        if (mutate_arg && (len <= IOCTL_BUFSZ)) {
            memcpy(str, buf, len);
        }
        if (ret < 0) {
            PyErr_SetFromErrno(PyExc_IOError);
            return NULL;
        }
        if (mutate_arg) {
            return PyInt_FromLong(ret);
        }
        else {
            return PyString_FromStringAndSize(buf, len);
        }
    }

    PyErr_Clear();
    if (PyArg_ParseTuple(args, "O&Is#:ioctl",
                         conv_descriptor, &fd, &code, &str, &len)) {
        if (len > IOCTL_BUFSZ) {
            PyErr_SetString(PyExc_ValueError,
                            "ioctl string arg too long");
            return NULL;
        }
        memcpy(buf, str, len);
        buf[len] = '\0';
        Py_BEGIN_ALLOW_THREADS
        ret = ioctl(fd, code, buf);
        Py_END_ALLOW_THREADS
        if (ret < 0) {
            PyErr_SetFromErrno(PyExc_IOError);
            return NULL;
        }
        return PyString_FromStringAndSize(buf, len);
    }

    PyErr_Clear();
    arg = 0;
    if (!PyArg_ParseTuple(args,
         "O&I|i;ioctl requires a file or file descriptor,"
         " an integer and optionally an integer or buffer argument",
                          conv_descriptor, &fd, &code, &arg)) {
      return NULL;
    }
    Py_BEGIN_ALLOW_THREADS
#ifdef __VMS
    ret = ioctl(fd, code, (void *)arg);
#else
    ret = ioctl(fd, code, arg);
#endif
    Py_END_ALLOW_THREADS
    if (ret < 0) {
        PyErr_SetFromErrno(PyExc_IOError);
        return NULL;
    }
    return PyInt_FromLong((long)ret);
#undef IOCTL_BUFSZ
}
