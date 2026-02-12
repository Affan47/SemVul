static PyObject *Input_read(InputObject *self, PyObject *args)
{
    long size = -1;

    PyObject *result = NULL;
    char *buffer = NULL;
    apr_size_t length = 0;
    int init = 0;

    apr_size_t n;

    if (!self->r) {
        PyErr_SetString(PyExc_RuntimeError, "request object has expired");
        return NULL;
    }

    if (!PyArg_ParseTuple(args, "|l:read", &size))
        return NULL;

#if defined(MOD_WSGI_WITH_DAEMONS)
    if (wsgi_inactivity_timeout) {
        apr_thread_mutex_lock(wsgi_shutdown_lock);
        wsgi_inactivity_shutdown_time = apr_time_now();
        wsgi_inactivity_shutdown_time += wsgi_inactivity_timeout;
        apr_thread_mutex_unlock(wsgi_shutdown_lock);
    }
#endif

    init = self->init;

    if (!self->init) {
        if (!ap_should_client_block(self->r))
            self->done = 1;

        self->init = 1;
    }


    if (self->done && self->length == 0)
        return PyString_FromString("");


    if (size == 0) {
        if (!init) {
            char dummy[1];

            Py_BEGIN_ALLOW_THREADS
            n = ap_get_client_block(self->r, dummy, 0);
            Py_END_ALLOW_THREADS

            if (n == -1) {
                PyErr_SetString(PyExc_IOError, "request data read error");
                return NULL;
            }
        }

        return PyString_FromString("");
    }


    if (size > 0) {


        result = PyString_FromStringAndSize(NULL, size);

        if (!result)
            return NULL;

        buffer = PyString_AS_STRING((PyStringObject *)result);


        if (self->buffer && self->length) {
            if (size >= self->length) {
                length = self->length;
                memcpy(buffer, self->buffer + self->offset, length);
                self->offset = 0;
                self->length = 0;
            }
            else {
                length = size;
                memcpy(buffer, self->buffer + self->offset, length);
                self->offset += length;
                self->length -= length;
            }
        }


        if (!self->length) {
            free(self->buffer);
            self->buffer = NULL;
        }


        if (length < size) {
            while (length != size) {
                Py_BEGIN_ALLOW_THREADS
                n = ap_get_client_block(self->r, buffer + length,
                                        size - length);
                Py_END_ALLOW_THREADS

                if (n == -1) {
                    PyErr_SetString(PyExc_IOError, "request data read error");
                    Py_DECREF(result);
                    return NULL;
                }
                else if (n == 0) {


                    self->done = 1;
                    break;
                }

                length += n;
            }


            if (length != size) {
                if (_PyString_Resize(&result, length))
                    return NULL;
            }
        }
    }
    else {


        size = self->length;

        if (!self->r->read_chunked && self->r->remaining > 0)
            size += self->r->remaining;

        size = size + (size >> 2);

        if (size < 256)
            size = self->r->read_chunked ? 8192 : 256;


        result = PyString_FromStringAndSize(NULL, size);

        if (!result)
            return NULL;

        buffer = PyString_AS_STRING((PyStringObject *)result);


        if (self->buffer && self->length) {
            length = self->length;
            memcpy(buffer, self->buffer + self->offset, length);
            self->offset = 0;
            self->length = 0;

            free(self->buffer);
            self->buffer = NULL;
        }


        Py_BEGIN_ALLOW_THREADS
        n = ap_get_client_block(self->r, buffer + length, size - length);
        Py_END_ALLOW_THREADS

        if (n == -1) {
            PyErr_SetString(PyExc_IOError, "request data read error");
            Py_DECREF(result);
            return NULL;
        }
        else if (n == 0) {


            self->done = 1;
        }

        length += n;


        while (!self->done) {
            if (length == size) {


                size = size + (size >> 2);

                if (_PyString_Resize(&result, size))
                    return NULL;

                buffer = PyString_AS_STRING((PyStringObject *)result);
            }


            Py_BEGIN_ALLOW_THREADS
            n = ap_get_client_block(self->r, buffer + length, size - length);
            Py_END_ALLOW_THREADS

            if (n == -1) {
                PyErr_SetString(PyExc_IOError, "request data read error");
                Py_DECREF(result);
                return NULL;
            }
            else if (n == 0) {


                self->done = 1;
            }

            length += n;
        }


        if (length != size) {
            if (_PyString_Resize(&result, length))
                return NULL;
        }
    }

    return result;
}
